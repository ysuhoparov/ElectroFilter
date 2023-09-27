#include "catalogmodel.h"


CatalogModel::CatalogModel(const size_t currentCatalogId)
{
    model = new QSqlQueryModel;

    catalogId = currentCatalogId;
    if(catalogId >= (size_t)Catalogs::max)
        catalogId = (size_t)Catalogs::max - 1;
}

CatalogModel::~CatalogModel()
{
    delete model;

}

QSqlQueryModel* CatalogModel::getData()
{
    model->setQuery(dataset[catalogId]);
    return model;
}


QSqlQueryModel* CatalogModel::getChoices()
{
    choice = new QSqlQueryModel;
    choice->setQuery(choicesset[catalogId]);
    return choice;
}


QString CatalogModel::getName(int editableId)
{
    query.prepare(nameset[catalogId]);
    query.bindValue(":editableId", editableId);
    query.exec();
    query.next();

    return query.value(0).toString();
}


QString CatalogModel::getChoice(int editableId)
{
    query.prepare(choiceset[catalogId]);
    query.bindValue(":editableId", editableId);
    query.exec();
    query.next();

    return query.value(0).toString();
}


int CatalogModel::getChoiceId(const QString& choice){
    query.prepare(choiceidset[catalogId]);
    query.bindValue(":choice", choice);
    query.exec();
    query.next();
    return query.value(0).toInt();
}


void CatalogModel::store(bool editable, int editableId, const QString& content)
{
    if(editable) {
        query.prepare(updateset[catalogId]);
        query.bindValue(":editableId", editableId);
    }
    else {
        query.prepare(insertset[catalogId]);
    }
    query.bindValue(":content", content);
    query.exec();
}


void CatalogModel::store(bool editable, int editableId, const QString& content, int  choiceId)
{
    if(editable) {
        query.prepare(updateset[catalogId]);
        query.bindValue(":editableId", editableId);
    }
    else {
        query.prepare(insertset[catalogId]);
    }
    query.bindValue(":content", content);
    query.bindValue(":choiceId",  choiceId);
    query.exec();
}


void CatalogModel::erase(int editableId)
{
    query.prepare(eraseset[catalogId]);
    query.bindValue(":editableId", editableId);

    query.exec();
}


