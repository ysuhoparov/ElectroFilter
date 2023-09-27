#ifndef CATALOGMODEL_H
#define CATALOGMODEL_H

#include "enums.h"

#include <QSqlQuery>
#include <QSqlQueryModel>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE


class CatalogModel
{
public:
    CatalogModel(const size_t);
    ~CatalogModel();

    QSqlQueryModel* getData();
    QSqlQueryModel* getChoices();
    QString getName(int);
    QString getChoice(int);

    int getChoiceId(const QString&);
    void store(bool, int, const QString&);
    void store(bool, int, const QString&, int);
    void erase(int);

private:
    size_t catalogId;
    QSqlQuery query;
    QSqlQueryModel* model;
    QSqlQueryModel* choice;

    const static int NQ = (int)Catalogs::max;   // enums.h

    QString dataset[NQ] { "select Id as №, spare as Запчасть from spares limit 40",
                          "select Id as №, role as 'Роль сотрудника' from roles limit 40",
                    "select employees.Id as №, employee as Работник, role as Роль "
                      "from employees, roles where roles.Id = employees.roleId limit 40",
                    "select Id as №, type as 'Вид оборудования' from types limit 40",
                    "select equipments.Id as №, equipment as Оборудование, type as Вид "
                      "from equipments, types where types.Id = equipments.typeId limit 40" };  //TableView

    QString choicesset[NQ] = {  "", "",  "select role from roles", "",
                                "select type from types" };         // ComboBox

    QString nameset[NQ] { "select spare from spares where Id = :editableId",
                          "select role from roles where Id = :editableId",
                        "select employee, role from employees, roles "
                          "where employees.Id = :editableId and roleId = roles.Id",
                        "select type from types where Id = :editableId",
                        "select equipment, type from equipments, types "
                          "where equipments.Id = :editableId and typeId = types.Id" };

    QString choiceset[NQ] { "", "", "select role from employees, roles "
                             "where employees.Id = :editableId and roleId = roles.Id",
                            "" ,    "select type from equipments, types "
                             "where equipments.Id = :editableId and typeId = types.Id" };

    QString choiceidset[NQ] = { "", "",
                                "select id from roles where role = :choice",
                                "", "select id from types where type = :choice"};

    QString insertset[NQ] { "insert into spares (spare) values(:content)",
                            "insert into roles (role) values(:content)",
                "insert into employees (employee, roleId) values(:content, :choiceId)",
                            "insert into types (type) values(:content)",
                "insert into equipments (equipment, typeId) values(:content, :choiceId)" };

    QString updateset[NQ] { "update spares set spare = :content where Id = :editableId",
                            "update roles set role = :content where Id = :editableId",
        "update employees set employee = :content, roleId = :choiceId where Id = :editableId",
                            "update types set type = :content where Id = :editableId",
        "update equipments set equipment = :content, typeId = :choiceId where Id = :editableId" };

    QString eraseset[NQ] {  "delete from spares where Id = :editableId",
                            "delete from roles where Id = :editableId",
                            "delete from employees where Id = :editableId",
                            "delete from types where Id = :editableId",
                            "delete from equipments where Id = :editableId" };
};

#endif // CATALOGMODEL_H
