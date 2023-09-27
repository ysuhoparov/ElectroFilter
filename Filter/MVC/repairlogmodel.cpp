#include "repairlogmodel.h"
#include <QDateTime>

RepairLogModel::RepairLogModel()
{
    queryGet = "select repairs.Id as №, STRFTIME('%d.%m.%Y', date) as Дата, "
               "field as Поле, content as Содержание, "
               "spare as Запчасть, employee as Исполнитель "
               "from repairs, employees, spares "
               "where repairs.employeeId = employees.id "
               "and repairs.spareId = spares.id and date >= :date";

    queryRow = "select date, field, content, spare, employee "
               "from repairs, employees, spares "
               "where repairs.employeeId = employees.id "
               "and repairs.spareId = spares.id and repairs.Id = :editableId ";

    queryInsert = "insert into repairs (date, field, content, employeeId, spareId) "
                  "values( :date, :field, :content, :employeeId, :spareId)";

    queryUpdate = "update repairs set date = :date, field = :field, "
                  "content = :content, employeeId = :employeeId, spareId = :spareId "
                  "where Id = :editableId ";

    queryDelete = "delete from repairs where Id = :editableId";

}


void RepairLogModel::store(bool editable, QVector<QString>& data, QDateTime date)
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
    query.bindValue(":spareId", getSpareId(data.at(1)));

    query.exec();
}

