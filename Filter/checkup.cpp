#include "checkup.h"

#include <QtWidgets>
#include <QSqlQueryModel>

Checkup::Checkup(QWidget *parent) : QDialog(parent)
{
    createTableGroupBox();
    createInputGroupBox();
    createButtonBox();

    employeeId = 1;
    isEditable = false;
    refresh();

    mainLayout = new QGridLayout;
    mainLayout->addWidget(tableGroupBox, 0, 0);
    mainLayout->addWidget(inputGroupBox, 1, 0);
    mainLayout->addWidget(buttonBox, 2, 0);
    setLayout(mainLayout);

    resize(size()/4*5);
    setWindowTitle(tr("Ведение оперативного журнала."));
}


void Checkup::refresh()
{
    query.prepare("select operationalLog.Id as №, STRFTIME('%d.%m.%Y %H:%M', date) as Дата, "
                  "content as Замечания, employee as Дежурный "
                  "from operationallog, employees "
                  "where operationalLog.employeeId = employees.id and date >= :date "
                  "limit 40");
    query.bindValue(":date", startDate->date());

    query.exec();
    model->setQuery(query);

    tableView->setModel(model);
    tableView->resizeColumnsToContents();
    tableView->scrollToBottom();

    if(isEditable) {
        inputGroupBox->setTitle(tr("Редактирование записи"));
        deleteButton->hide();
    }
    else {
        inputGroupBox->setTitle(tr("Ввод новой записи"));
        deleteButton->show();
    }
}


void Checkup::createTableGroupBox()
{
    tableView = new QTableView;
    model = new QSqlQueryModel;
    startDate = new QDateEdit(QDate::currentDate().addMonths(-1));
    startDate->setCalendarPopup (true);
    startDate->setFixedWidth(100);
    labelStartDate= new QLabel(tr("Показывать данные начиная с даты: ")) ;

    dateFrame = new QFrame;
    dateLayout = new QHBoxLayout;
    dateLayout->addWidget(labelStartDate);
    dateLayout->addWidget(startDate);
    dateLayout->addStretch();
    dateFrame->setLayout(dateLayout);

    tableGroupBox = new QGroupBox(tr("Оперативный журнал"));
    tableLayout = new QGridLayout;
    tableLayout->addWidget(tableView);
    tableLayout->addWidget(dateFrame);
    tableGroupBox->setLayout(tableLayout);

    connect(startDate, &QDateEdit::userDateChanged, this, &Checkup::refresh);
    connect(tableView, &QTableView::doubleClicked, this, &Checkup::edit);
}


void Checkup::createInputGroupBox()
{
    inputGroupBox = new QGroupBox;

    employeeComboBox = new QComboBox;
    employeeModel = new QSqlQueryModel;
    employeeModel->setQuery("select employee from employees where roleId <= 2");
    employeeComboBox->setModel(employeeModel);

    content = new QLineEdit;

    inputLayout = new QGridLayout;
    inputLayout->addWidget(employeeComboBox, 0, 0);
    inputLayout->addWidget(content, 0, 1);
    inputGroupBox->setLayout(inputLayout);
}

void Checkup::createButtonBox()
{
    buttonBox = new QDialogButtonBox;

    saveButton = buttonBox->addButton(QDialogButtonBox::Save);
    cancelButton = buttonBox->addButton(QDialogButtonBox::Cancel);
    closeButton = buttonBox->addButton(QDialogButtonBox::Close);

    deleteButton = buttonBox->addButton("Delete", QDialogButtonBox::ActionRole);

    connect(saveButton, &QPushButton::clicked, this, &Checkup::save);
    connect(cancelButton, &QPushButton::clicked, this, &Checkup::cancel);
    connect(closeButton, &QPushButton::clicked, this, &Checkup::close);
    connect(deleteButton, &QPushButton::clicked, this, &Checkup::erase);
}


void Checkup::save()
{
    query.prepare("select id from employees where employee = :employee");
    query.bindValue(":employee", employeeComboBox->currentText());
    query.exec();
    query.next();
    employeeId = query.value(0).toInt();

    if(isEditable) {
        query.prepare("update operationallog set content = :content, employeeid = :employeeid "
                      "where id = :editableId ");
        query.bindValue(":editableId", editableId);
    }
    else  {
        query.prepare("insert into operationallog (date, content, employeeid) "
                      "values( :date, :content, :employeeid)" );
        query.bindValue(":date", QDateTime::currentDateTime());
    }

    query.bindValue(":content", content->text());
    query.bindValue(":employeeid", employeeId);
    query.exec();

    isEditable = false;
    refresh();
}


void Checkup::cancel()
{
    if(isEditable)
        isEditable = false;
    else
        content->setText("");
}


void Checkup::edit()
{
    isEditable = true;
    inputGroupBox->setTitle(tr("Редактирование записи"));
    deleteButton->hide();
    editableId = model->data(model->index(tableView->currentIndex().row(), 0), Qt::DisplayRole).toInt();

    query.prepare("select content, employee "
                  "from operationallog, employees "
                  "where operationalLog.employeeId = employees.Id "
                  "and operationalLog.Id = :editableId");

    query.bindValue(":editableId", editableId);
    query.exec();
    query.next();

    content->setText(query.value(0).toString());

    int index = employeeComboBox->findText(query.value(1).toString());
    if(index != -1)
        employeeComboBox->setCurrentIndex(index);

}


void Checkup::erase()
{
    if(isEditable) return;

    int key =  QMessageBox::question(this, "Внимание!", "Запись будет удалена из журнала! ");
    switch (key) {
    case QMessageBox::Yes:
        editableId = model->data(model->index(tableView->currentIndex().row(), 0), Qt::DisplayRole).toInt();
        query.prepare("delete from operationallog where Id = :editableId");
        query.bindValue(":editableId", editableId);
        query.exec();
        refresh();
        break;
    case QMessageBox::No:
        break;
    }

}
