
#ifndef CHANNEL_H
#define CHANNEL_H

#include <QString>
#include <QObject>
#include <QThread>
#include <QQueue>

#include "netinfo.h"

class Channel: public QObject
{
    Q_OBJECT

    friend class TestFilter;

    unsigned char *demoData;
    const int nField = 8;
    const unsigned char startCoronation = 18;
    const unsigned char uSpark = 48;
    const unsigned char uSlow = 32;
    const int scale = 40;

    void makeUfilter(int);
    void makeIfilter(int);

    NetInfo controllerData;
    unsigned char command;
    uint status;   // Пуск / Стоп

public:
    Channel();
    ~Channel();

    static QQueue<unsigned char> queueCommand;

 public slots:
    void simulateData();

signals:
    void send(NetInfo);

};

#endif // CHANNEL_H
