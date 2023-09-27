#include "servicelogmodel.h"

#include <QDateTime>

ServiceLogModel::ServiceLogModel()
{
    queryGet = "select services.Id as №, STRFTIME('%d.%m.%Y', date) as Дата, "
               "field as Поле, content as Содержание, "
               "equipment as Запчасть, employee as Исполнитель "
               "from services, employees, equipments "
               "where services.employeeId = employees.id "
               "and services.equipmentId = equipments.id and date >= :date";

    queryRow = "select date, field, content, equipment, employee "
               "from services, employees, equipments "
               "where services.employeeId = employees.id "
               "and services.equipmentId = equipments.id and services.Id = :editableId ";

    queryInsert = "insert into services (date, field, content, employeeId, equipmentId) "
                  "values( :date, :field, :content, :employeeId, :equipmentId)";

    queryUpdate = "update services set date = :date, field = :field, "
                  "content = :content, employeeId = :employeeId, equipmentId = :equipmentId "
                  "where Id = :editableId ";

    queryDelete = "delete from services where Id = :editableId";

}


void ServiceLogModel::store(bool editable, QVector<QString>& data, QDateTime date)
{
    if(editable) {
        query.prepare(queryUpdate);
        query.bindValue(":editableId", data.at(2));
    }
    else {
        query.prepare(queryInsert);
    }

    query.bindValue(":date", date.date());
    query.bindValue(":field", data.at(3));
    query.bindValue(":content", data.at(4));

    query.bindValue(":employeeId", getEmployeeId(data.at(0)));
    query.bindValue(":equipmentId", getEquipmentId(data.at(1)));
    query.exec();

}
