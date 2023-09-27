#include "catalogview.h"
#include "catalogmodel.h"
#include <QtWidgets>


CatalogView::CatalogView(size_t catalogid, QWidget *parent) : QDialog(parent)
{
    model = new CatalogModel(catalogid);
    mainLayout = new QGridLayout;

    setWindowTitle(title[catalogid]);
    editable = false;
}

CatalogView::~CatalogView()
{
    delete model;
}

void CatalogView::open()
{
    createTableGroupBox();
    createInputGroupBox();
    createButtonBox();

    mainLayout->addWidget(tableGroupBox, 0, 0);
    mainLayout->addWidget(inputGroupBox, 1, 0);
    mainLayout->addWidget(buttonBox, 2, 0);
    setLayout(mainLayout);

    resize( width, height);
    refresh();
    show();
}


void CatalogView::refresh()
{
    tableView->setModel(model->getData());
    tableView->resizeColumnsToContents();
    tableView->scrollToBottom();

    inputGroupBox->setTitle(tr("Ввод новой записи"));
    deleteButton->setEnabled(true);
}

void CatalogView::createTableGroupBox()
{
    tableView = new QTableView;
    //    tableView->setSortingEnabled(true);

    tableGroupBox = new QGroupBox(tr("Данные справочника"));
    tableLayout = new QGridLayout;
    tableLayout->addWidget(tableView);

    tableGroupBox->setLayout(tableLayout);

    connect(tableView, &QTableView::doubleClicked, this, &CatalogView::edit);
}

void CatalogView::createInputGroupBox()
{
    content = new QLineEdit;
    content->setPlaceholderText("Наименоивание");

    inputLayout = new QGridLayout;
    inputLayout->addWidget(content, 0, 0);

    inputGroupBox = new QGroupBox;
    inputGroupBox->setLayout(inputLayout);
}

void CatalogView::createButtonBox()
{
    buttonBox = new QDialogButtonBox;

    saveButton = buttonBox->addButton(QDialogButtonBox::Save);
    cancelButton = buttonBox->addButton(QDialogButtonBox::Cancel);
    closeButton = buttonBox->addButton(QDialogButtonBox::Close);

    deleteButton = buttonBox->addButton("Delete", QDialogButtonBox::ActionRole);

    connect(saveButton, &QPushButton::clicked, this, &CatalogView::save);
    connect(cancelButton, &QPushButton::clicked, this, &CatalogView::cancel);
    connect(closeButton, &QPushButton::clicked, this, &CatalogView::close);
    connect(deleteButton, &QPushButton::clicked, this, &CatalogView::erase);
}


void CatalogView::save()
{
    model->store(editable, editableId, content->text());
    editable = false;
    refresh();
}

void CatalogView::cancel()
{
    if(editable) {
        editable = false;
        inputGroupBox->setTitle(tr("Ввод новой записи"));
        deleteButton->setEnabled(true);
    }
    else
        content->setText("");
}

void CatalogView::edit()
{
    editable = true;
    inputGroupBox->setTitle(tr("Редактирование записи"));
    deleteButton->setEnabled(false);
    editableId = tableView->model()->data(tableView->model()->index(tableView->currentIndex().row(), 0), \
                                          Qt::DisplayRole).toInt();

    bring();
}

void CatalogView::bring()
{
    content->setText(model->getName(editableId));
}


void CatalogView::erase()
{
    int key =  QMessageBox::question(this, "Внимание!", "Запись будет удалена! ");
    switch (key) {
    case QMessageBox::Yes:
        editableId = tableView->model()->data(tableView->model()->index(tableView->currentIndex().row(), 0), \
                                              Qt::DisplayRole).toInt();
        model->erase(editableId);
        refresh();
        break;
    case QMessageBox::No:
        break;
    }
}



