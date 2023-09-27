#ifndef CATALOGVIEW_H
#define CATALOGVIEW_H

#include <QDialog>

#include "enums.h"

QT_BEGIN_NAMESPACE
class QDialog;
class QGroupBox;
class QGridLayout;
class QDialogButtonBox;
class QPushButton;
class QLineEdit;
class QTableView;
class CatalogModel;
QT_END_NAMESPACE


class CatalogView : public QDialog
{
    Q_OBJECT

public:
    CatalogView(size_t id, QWidget *parent = nullptr);
    ~CatalogView();
    void open();

protected slots:
    virtual void save();
    void cancel();
    void edit();
    virtual void bring();
    void erase();
    void refresh();

protected:
    void createTableGroupBox();
    virtual void createInputGroupBox();
    void createButtonBox();


    int editableId;
    bool editable;

    QGroupBox* tableGroupBox;

    QTableView* tableView;
    CatalogModel* model;

    QGroupBox* inputGroupBox;
    QLineEdit* content;


    QDialogButtonBox* buttonBox;
    QPushButton* saveButton;
    QPushButton* cancelButton;
    QPushButton* closeButton;
    QPushButton* deleteButton;

    QGridLayout* mainLayout;
    QGridLayout* tableLayout;
    QGridLayout* inputLayout;

    const static int NQ = (int)Catalogs::max;   // enums.h
    QString title[NQ] {"Запчасти", "Роли сотрудников", "Служащие", "Виды оборудования", "Оборудование в эксплуатации"};

    int width=600, height=600;

};

#endif // CATALOGVIEW_H
