#ifndef REPAIRLOGMODEL_H
#define REPAIRLOGMODEL_H

#include "abstractlogmodel.h"

class RepairLogModel : public AbstractLogModel
{


public:
    RepairLogModel();

    void store(bool, QVector<QString>&, QDateTime) override;

};

#endif // REPAIRLOGMODEL_H


