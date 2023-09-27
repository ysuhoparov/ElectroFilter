#ifndef SERVICELOGVIEW_H
#define SERVICELOGVIEW_H

#include "abstractlogview.h"

class ServiceLogView : public AbstractLogView
{
    QComboBox* equipmentComboBox;
    QDateEdit* serviceDate;
    QLineEdit * field;
public:
    ServiceLogView(QWidget *parent);
    ~ServiceLogView();
    void createInputGroupBox() override;
    void save() override;
    void bring() override;
};

#endif // SERVICELOGVIEW_H
