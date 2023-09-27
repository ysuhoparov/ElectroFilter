#ifndef MODEL_H
#define MODEL_H


#include "field.h"

#include "netinfo.h"
#include "qtypes.h"

class Model
{

public:
    Model();

    void store(Field** fields, const int zones) const;
    quint64 incode(const NetInfo&) const;
    NetInfo decode(quint64);

    bool isOpen = false;

};

#endif // MODEL_H
