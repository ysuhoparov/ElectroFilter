#include "servicelogview.h"

#include "servicelogview.h"
#include "servicelogmodel.h"

#include <QComboBox>
#include <QDateEdit>
#include <QDateTime>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>

ServiceLogView::ServiceLogView(QWidget *parent) : AbstractLogView(parent)
{
    model = new ServiceLogModel;
    title = tr("Журнал обслуживания оборудования");
}

ServiceLogView::~ServiceLogView()
{
    delete model;
}


void ServiceLogView::createInputGroupBox()
{
    equipmentComboBox = new QComboBox;
    equipmentComboBox->setModel(model->getList("select equipment from equipments"));
    equipmentComboBox->setModel(model->getList(model->queryEquipments));

    serviceDate = new QDateEdit(QDate::currentDate());
    serviceDate->setCalendarPopup (true);

    content = new QLineEdit;
    content->setPlaceholderText("Описание работ");

    field = new QLineEdit;
    field->setPlaceholderText("№ поля");
    field->setMaximumWidth(120);

    inputLayout = new QGridLayout;
    inputLayout->addWidget(serviceDate, 0, 0);
    inputLayout->addWidget(equipmentComboBox, 0, 1);
    inputLayout->addWidget(employeeComboBox, 0, 2);

    inputLayout->addWidget(content, 1, 1);
    inputLayout->addWidget(field, 1, 2);

    inputGroupBox = new QGroupBox;
    inputGroupBox->setLayout(inputLayout);

}

void ServiceLogView::save()
{
    QVector<QString> data;
    data.emplace_back(employeeComboBox->currentText());
    data.emplace_back(equipmentComboBox->currentText());

    data.emplace_back(QString("%1").arg(editableId));

    data.emplace_back(field->text());
    data.emplace_back(content->text());

    //qDebug() <<  data.at(1) <<  "  "<< data.at(2)<<  "  "<< data.at(3);

    model->store(editable, data, serviceDate->dateTime());

    editable = false;
    refresh();
}

void ServiceLogView::bring()
{
    auto editableRow = model->getRow(editableId);

    serviceDate->setDate(editableRow.value(0).toDate());
    field->setText(editableRow.value(1).toString());

    content->setText(editableRow.value(2).toString());

    int index = employeeComboBox->findText(editableRow.value(4).toString());
    if(index != -1)
        employeeComboBox->setCurrentIndex(index);

    index = equipmentComboBox->findText(editableRow.value(3).toString());
    if(index != -1)
        equipmentComboBox->setCurrentIndex(index);

}

