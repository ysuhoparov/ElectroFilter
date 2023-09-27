#ifndef OPERATIVELOGMODEL_H
#define OPERATIVELOGMODEL_H

#include "abstractlogmodel.h"

class OperativeLogModel : public AbstractLogModel
{

public:
    OperativeLogModel();

    void store(bool, QVector<QString>&, QDateTime) override;

};

#endif // OPERATIVELOGMODEL_H
