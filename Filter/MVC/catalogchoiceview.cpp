#include "catalogchoiceview.h"
#include "catalogmodel.h"

#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>


CatalogChoiceView::CatalogChoiceView(size_t id, QWidget *parent) : CatalogView(id, parent) {}


void CatalogChoiceView::save()
{
    model->store(editable, editableId, content->text(), model->getChoiceId(choiceComboBox->currentText()));
    editable = false;
    refresh();
}


void CatalogChoiceView::createInputGroupBox()
{
    content = new QLineEdit;
    content->setPlaceholderText("Наименоивание");

    inputLayout = new QGridLayout;
    inputLayout->addWidget(content, 0, 0);

    choiceComboBox = new QComboBox;
    choiceComboBox->setModel(model->getChoices());
    inputLayout->addWidget(choiceComboBox, 0, 1);

    inputGroupBox = new QGroupBox;
    inputGroupBox->setLayout(inputLayout);
}


void CatalogChoiceView::bring()
{
    content->setText(model->getName(editableId));

    int index = choiceComboBox->findText(model->getChoice(editableId));
    if(index != -1)
        choiceComboBox->setCurrentIndex(index);

}





