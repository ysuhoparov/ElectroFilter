
#include "operativelogview.h"
#include "operativelogmodel.h"
#include "qdatetime.h"

#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>

/*CatalogChoiceView::CatalogChoiceView(size_t id, QWidget *parent) : CatalogView(id, parent) {}
AbstractLogView::AbstractLogView(QWidget *parent) : QDialog(parent)*/
OperativeLogView::OperativeLogView(QWidget *parent) : AbstractLogView(parent)
{
    model = new OperativeLogModel;
    title = "Оперативный журнал";
}

OperativeLogView::~OperativeLogView()
{
    delete model;
}


void OperativeLogView::createInputGroupBox()
{
    inputGroupBox = new QGroupBox;

//    employeeComboBox = new QComboBox;
//    employeeComboBox->setModel(model->getList("select employee from employees"));

    content = new QLineEdit;

    inputLayout = new QGridLayout;
    inputLayout->addWidget(content, 0, 0);
    inputLayout->addWidget(employeeComboBox, 0, 1);
    inputGroupBox->setLayout(inputLayout);

 // connect(employeeComboBox, &QComboBox::currentIndexChanged, this, &OperativeLogView::filterOnEmployee);
}

void OperativeLogView::save()
{   
    QVector<QString> data;
    data.emplace_back(employeeComboBox->currentText());
    data.emplace_back(QString("%1").arg(editableId));
    data.emplace_back(content->text());

    model->store(editable, data, QDateTime::currentDateTime());
    editable = false;
    refresh();
}

void OperativeLogView::bring()
{
    auto editableRow = model->getRow(editableId);
    content->setText(editableRow.value(0).toString());

    int index = employeeComboBox->findText(editableRow.value(1).toString());
    if(index != -1)
        employeeComboBox->setCurrentIndex(index);
}



