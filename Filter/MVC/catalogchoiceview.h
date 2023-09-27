#ifndef CATALOGCHOICEVIEW_H
#define CATALOGCHOICEVIEW_H

#include "catalogview.h"

QT_BEGIN_NAMESPACE
class QComboBox;
QT_END_NAMESPACE


class CatalogChoiceView : public CatalogView
{

    void createInputGroupBox() override;
    void save() override;
    void bring() override;

    QComboBox* choiceComboBox;

public:
    CatalogChoiceView(size_t id, QWidget *parent = nullptr);


};


#endif // CATALOGCHOICEVIEW_H
