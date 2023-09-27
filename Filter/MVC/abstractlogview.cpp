#include <QtWidgets>
#include <QSqlQueryModel>

#include "abstractlogview.h"
#include "abstractlogModel.h"

AbstractLogView::AbstractLogView(QWidget *parent) : QDialog(parent)
{
    editable = false;
}


void AbstractLogView::open()
{
    mainLayout = new QGridLayout;

    createTableGroupBox();
    createInputGroupBox();
    createButtonBox();

    mainLayout->addWidget(tableGroupBox, 0, 0);
    mainLayout->addWidget(inputGroupBox, 1, 0);
    mainLayout->addWidget(buttonBox, 2, 0);
    setLayout(mainLayout);

    setWindowTitle(title);
    resize( width, height);
    refresh();
    show();     
}


void AbstractLogView::refresh()
{
    tableView->setModel(model->get(startDate->date()));
    tableView->setColumnHidden(0, true);
    tableView->resizeColumnsToContents();
    tableView->scrollToBottom();

    inputGroupBox->setTitle(tr("Ввод новой записи"));
    deleteButton->setEnabled(true);
}


void AbstractLogView::createTableGroupBox()
{
    tableView = new QTableView;

    startDate = new QDateEdit(QDate::currentDate().addMonths(-1));
    startDate->setCalendarPopup (true);
    startDate->setFixedWidth(100);
    labelStartDate= new QLabel(tr("Дата начала : ")) ;

    radioButtonEmpl = new QRadioButton("Фильтр по выбранному сотруднику");

    dateFrame = new QFrame;
    dateLayout = new QHBoxLayout;
    dateLayout->addWidget(labelStartDate);
    dateLayout->addWidget(startDate);
    dateLayout->addStretch();
    dateLayout->addWidget(radioButtonEmpl);
    dateFrame->setLayout(dateLayout);

    tableGroupBox = new QGroupBox(tr("Текущие данные"));
    tableLayout = new QGridLayout;
    tableLayout->addWidget(tableView);
    tableLayout->addWidget(dateFrame);
    tableGroupBox->setLayout(tableLayout);

    connect(tableView, &QTableView::doubleClicked, this, &AbstractLogView::edit);
    connect(startDate, &QDateEdit::userDateChanged, this, &AbstractLogView::refresh);
    connect(radioButtonEmpl, &QPushButton::clicked, this, &AbstractLogView::filterOnEmployee);

    employeeComboBox = new QComboBox;
    employeeComboBox->setModel(model->getList(model->queryEmployees));
    connect(employeeComboBox, &QComboBox::currentIndexChanged, this, &AbstractLogView::filterOnEmployee);

}


void AbstractLogView::createButtonBox()
{
    buttonBox = new QDialogButtonBox;

    saveButton = buttonBox->addButton(QDialogButtonBox::Save);
    cancelButton = buttonBox->addButton(QDialogButtonBox::Cancel);
    closeButton = buttonBox->addButton(QDialogButtonBox::Close);

    deleteButton = buttonBox->addButton("Delete", QDialogButtonBox::ActionRole);

    connect(saveButton, &QPushButton::clicked, this, &AbstractLogView::save);
    connect(cancelButton, &QPushButton::clicked, this, &AbstractLogView::cancel);
    connect(closeButton, &QPushButton::clicked, this, &AbstractLogView::close);
    connect(deleteButton, &QPushButton::clicked, this, &AbstractLogView::erase);

}


void AbstractLogView::cancel()
{
    if(editable) {
        editable = false;
        inputGroupBox->setTitle(tr("Ввод новой записи"));
        deleteButton->setEnabled(true);
    }
    else
        content->setText("");

}


void AbstractLogView::edit()
{
    editable = true;
    inputGroupBox->setTitle(tr("Редактирование"));
    deleteButton->setEnabled(false);
    editableId = tableView->model()->data( \
        tableView->model()->index(tableView->currentIndex().row(), 0), Qt::DisplayRole).toInt();
    bring();

}


void AbstractLogView::erase()
{
    int key =  QMessageBox::question(this, "Внимание!", "Запись будет удалена! ");
    switch (key) {
    case QMessageBox::Yes:
        editableId = tableView->model()->data( \
            tableView->model()->index(tableView->currentIndex().row(), 0), Qt::DisplayRole).toInt();
        model->erase(editableId);
        refresh();
        break;
    case QMessageBox::No:
        break;
    }
}


void AbstractLogView::filterOnEmployee()
{
    if(radioButtonEmpl->isChecked())
        model->setEmployeeFiltered(model->getEmployeeId(employeeComboBox->currentText()));
    else
        model->setEmployeeFiltered(0);
    refresh();

}
