#include "operationallog.h"

OperationalLog::OperationalLog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    model = new QSqlQueryModel;
    employeeModel = new QSqlQueryModel;
    employeeId = 1;
    isEditable = false;
    refresh();
}


OperationalLog::~OperationalLog()
{
    delete model;
    delete employeeModel;

}


void OperationalLog::refresh()
{
    query.prepare("select operationalLog.Id, date as Дата, content as Замечания, employee as Дежурный "
                  "from operationallog, employees "
                  "where operationalLog.employeeId = employees.id and date >= :date");
    query.bindValue(":date", ui.startDate->date());

    query.exec();
    model->setQuery(query);

    ui.tableView->setModel(model);
    ui.tableView->resizeColumnsToContents();

    ui.dateEdit->setDate(QDate::currentDate());

    employeeModel->setQuery("select employee from employees");
    ui.employeeBox->setModel(employeeModel);

    if(!isEditable)
        ui.action->setText("Ввод новой записи");

}


void OperationalLog::on_startDate_userDateChanged()
{
    refresh();
}


void OperationalLog::on_savebtnBox_accepted()
{
    query.prepare("select id from employees where employee = :employee");
    query.bindValue(":employee", ui.employeeBox->currentText());
    query.exec();
    query.next();
    employeeId = query.value(0).toInt();

    if(isEditable) {
        query.prepare("update operationallog set date = :date, content = :content, "
                      "employeeid = :employeeid where id = :editableId ");
        query.bindValue(":editableId", editableId);
    } else {
        query.prepare("insert into operationallog (date, content, employeeid) "
                      "values( :date, :content, :employeeid)" );
    }
    query.bindValue(":date", ui.dateEdit->date());
    query.bindValue(":content", ui.contentEdit->text());
    query.bindValue(":employeeid", employeeId);
    query.exec();

    isEditable = false;
    refresh();
}


void OperationalLog::on_savebtnBox_rejected()
{
    ui.contentEdit->setText("");
    const QString itemText = ui.employeeBox->currentText();
    isEditable = false;

    refresh();

//    query.prepare("select employee from employees where id = :employeeId");   // alternative
//    query.bindValue(":employeeId", employeeId);
//    query.exec();
//    query.next();
//    const QString itemText = query.value(0).toString();
//    qDebug() << itemText;

    int index = ui.employeeBox->findText(itemText);
    if(index != -1)
        ui.employeeBox->setCurrentIndex(index);
}


void OperationalLog::on_editBtn_clicked()
{
    isEditable = true;
    ui.action->setText("Редактирование записи");
    editableId = model->data(model->index(ui.tableView->currentIndex().row(), 0), Qt::DisplayRole).toInt();

    query.prepare("select date, content, employee "
                  "from operationallog, employees "
                  "where operationalLog.employeeId = employees.Id"
                  " and operationalLog.Id = :editableId");
    query.bindValue(":editableId", editableId);
    query.exec();
    query.next();
    employeeId = query.value(0).toInt();

    ui.contentEdit->setText(query.value(1).toString());
    ui.dateEdit->setDate(query.value(0).toDate());
    int index = ui.employeeBox->findText(query.value(2).toString());
    if(index != -1)
        ui.employeeBox->setCurrentIndex(index);

}



//void OperationalLog::on_employeeBox_currentIndexChanged(int index)
//{

//}

