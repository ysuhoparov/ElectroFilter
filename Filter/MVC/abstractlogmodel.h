#ifndef ABSTRACTLOGMODEL_H
#define ABSTRACTLOGMODEL_H

#include <QSqlQuery>
#include <QSqlQueryModel>

class AbstractLogModel
{

public:
    AbstractLogModel();
    virtual ~AbstractLogModel();

    QSqlQueryModel* get(QDate);
    const QSqlQuery& getRow(int);
    virtual void store(bool, QVector<QString>&, QDateTime) = 0;
    void erase(int);

    void setEmployeeFiltered(int id){
        employeeFilteredId = id;
    }

    QSqlQueryModel* getList(const QString & query);
    int getEmployeeId(const QString& );
    int getSpareId(const QString&);
    int getEquipmentId(const QString&);

    QString queryEquipments;
    QString querySpares;
    QString queryEmployees;

protected:
    int employeeFilteredId;
    QSqlQueryModel* model;
    QSqlQueryModel* employees;
    QSqlQueryModel* spares;
    QSqlQuery query;

    QString queryGet;
    QString queryRow;
    QString queryInsert;
    QString queryUpdate;
    QString queryDelete;

    QString queryEmployeeId;
    QString querySpareId;
    QString queryEquipmentId;

    QList<QSqlQueryModel*> modelList;

};

#endif // ABSTRACTLOGMODEL_H

