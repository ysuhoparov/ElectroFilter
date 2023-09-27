#ifndef SERVICELOGMODEL_H
#define SERVICELOGMODEL_H

#include "abstractlogmodel.h"

class ServiceLogModel : public AbstractLogModel
{
public:
    ServiceLogModel();
    void store(bool, QVector<QString>&, QDateTime) override;
};

#endif // SERVICELOGMODEL_H

