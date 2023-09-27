#include "operativelogmodel.h"

#include <QDateTime>

OperativeLogModel::OperativeLogModel()
{
    queryGet = "select operationalLog.Id as №, STRFTIME('%d.%m.%Y %H:%M', date) as Дата, "
               "content as Замечания, employee as Дежурный "
               "from operationallog, employees "
               "where operationalLog.employeeId = employees.Id and date >= :date";

    queryRow = "select content, employee "
               "from operationallog, employees "
               "where operationalLog.employeeId = employees.Id "
               "and operationalLog.Id = :editableId";

    queryInsert = "insert into operationallog (date, content, employeeId) "
                  "values( :date, :content, :employeeId)";

    queryUpdate = "update operationallog set content = :content, employeeId = :employeeId "
                  "where Id = :editableId";

    queryDelete = "delete from operationallog where Id = :editableId";

}


void OperativeLogModel::store(bool editable, QVector<QString>& data, QDateTime date)
{        
    if(editable) {
        query.prepare(queryUpdate);
        query.bindValue(":editableId", data.at(1));
    }
    else {
        query.prepare(queryInsert);
        query.bindValue(":date", date);
    }
    query.bindValue(":content", data.at(2));
    query.bindValue(":employeeId", getEmployeeId(data.at(0)));
    query.exec();
}
