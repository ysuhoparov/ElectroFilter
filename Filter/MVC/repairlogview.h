#ifndef REPAIRLOGVIEW_H
#define REPAIRLOGVIEW_H

#include "abstractlogview.h"

class RepairLogView : public AbstractLogView
{
    QComboBox* spareComboBox;
    QDateEdit* repairDate;
    QLineEdit * field;

public:
    RepairLogView(QWidget *parent);
    ~RepairLogView();
    void createInputGroupBox() override;
    void save() override;
    void bring() override;

};

#endif // REPAIRLOGVIEW_H
