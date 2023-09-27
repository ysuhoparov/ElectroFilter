#include "abstractlogmodel.h"
#include "qdatetime.h"


AbstractLogModel::AbstractLogModel()
{
    model = new QSqlQueryModel;
    employeeFilteredId = 0;

    queryEmployeeId = "select id from employees where employee = :employee";
    querySpareId = "select id from spares where spare = :spare";
    queryEquipmentId = "select id from equipments where equipment = :equipment";

    queryEmployees = "select employee from employees";
    querySpares = "select spare from spares ";
    queryEquipments = "select equipment from equipments ";
}


AbstractLogModel::~AbstractLogModel()
{
    delete model;
}


QSqlQueryModel* AbstractLogModel::get(QDate date)
{
    if (employeeFilteredId)
        query.prepare(queryGet + " and employeeId=" +  QString::number(employeeFilteredId));
    else
        query.prepare(queryGet);

    query.bindValue(":date", date);
    query.exec();
    model->setQuery(query);
    return model;
}


const QSqlQuery& AbstractLogModel::getRow(int editableId)
{
    query.prepare(queryRow);
    query.bindValue(":editableId", editableId);
    query.exec();
    query.next();
    return  query;
}


void AbstractLogModel::erase(int editableId)
{
    query.prepare(queryDelete);
    query.bindValue(":editableId", editableId);
    query.exec();
}


QSqlQueryModel* AbstractLogModel::getList(const QString & query)
{
    modelList.insert(0, new QSqlQueryModel);
    modelList.at(0)->setQuery(query);
    return modelList.at(0);
}


int AbstractLogModel::getEmployeeId(const QString& employee)
{
    QSqlQuery query;
    query.prepare(queryEmployeeId);
    query.bindValue(":employee", employee);
    query.exec();
    query.next();
    return query.value(0).toInt();
}


int AbstractLogModel::getSpareId(const QString& spare)
{
    QSqlQuery query;
    query.prepare(querySpareId);
    query.bindValue(":spare", spare);
    query.exec();
    query.next();
    return query.value(0).toInt();
}


int AbstractLogModel::getEquipmentId(const QString& equipment)
{
    QSqlQuery query;
    query.prepare(queryEquipmentId);
    query.bindValue(":equipment", equipment);
    query.exec();
    query.next();
    return query.value(0).toInt();
}
