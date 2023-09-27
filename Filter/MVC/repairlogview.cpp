#include "repairlogview.h"
#include "repairlogmodel.h"

#include <QComboBox>
#include <QDateEdit>
#include <QDateTime>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>

RepairLogView::RepairLogView(QWidget *parent) : AbstractLogView(parent)
{
    model = new RepairLogModel;
    title = tr("Журнал ремонта");
}

RepairLogView::~RepairLogView()
{
    delete model;
}


void RepairLogView::createInputGroupBox()
{
    spareComboBox = new QComboBox;
    spareComboBox->setModel(model->getList(model->querySpares));

    repairDate = new QDateEdit(QDate::currentDate());
    repairDate->setCalendarPopup (true);

    content = new QLineEdit;
    content->setPlaceholderText("Описание работ");

    field = new QLineEdit;
    field->setPlaceholderText("№ поля");
    field->setMaximumWidth(120);

    inputLayout = new QGridLayout;
    inputLayout->addWidget(field, 0, 0);
    inputLayout->addWidget(spareComboBox, 0, 1);
    inputLayout->addWidget(employeeComboBox, 0, 2);
    inputLayout->addWidget(repairDate, 1, 0);
    inputLayout->addWidget(content, 1, 1);

    inputGroupBox = new QGroupBox;
    inputGroupBox->setLayout(inputLayout);
}

void RepairLogView::save()
{
    QVector<QString> data;
    data.emplace_back(employeeComboBox->currentText());
    data.emplace_back(spareComboBox->currentText());

    data.emplace_back(QString("%1").arg(editableId));

    data.emplace_back(field->text());
    data.emplace_back(content->text());

    model->store(editable, data, repairDate->dateTime());

    editable = false;
    refresh();
}

void RepairLogView::bring()
{
    auto editableRow = model->getRow(editableId);

    repairDate->setDate(editableRow.value(0).toDate());
    field->setText(editableRow.value(1).toString());

    content->setText(editableRow.value(2).toString());

    int index = employeeComboBox->findText(editableRow.value(4).toString());
    if(index != -1)
        employeeComboBox->setCurrentIndex(index);

    index = spareComboBox->findText(editableRow.value(3).toString());
    if(index != -1)
        spareComboBox->setCurrentIndex(index);

}
