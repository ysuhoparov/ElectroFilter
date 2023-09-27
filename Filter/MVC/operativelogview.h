#ifndef OPERATIVELOGVIEW_H
#define OPERATIVELOGVIEW_H

#include "abstractlogview.h"

class OperativeLogView : public AbstractLogView
{

public:
    OperativeLogView(QWidget *parent);
    ~OperativeLogView();
    void createInputGroupBox() override;
    void save() override;
    void bring() override;

};

#endif // OPERATIVELOGVIEW_H
