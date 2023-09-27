#include "channel.h"

Channel::Channel()
{
    demoData = new unsigned char[nField];

    for(unsigned char i = 0; i < nField; i++)
        demoData[i] = startCoronation + i % 3;

    command = 0;
    status = 255;
}

Channel::~Channel()
{
    delete demoData;
}

void Channel::makeUfilter(int i)
{
    // Имитация плавного подъема напряжения
    if(demoData[i] > uSlow + i * 2)
        if(rand() % (2 + demoData[i]/10))
            --demoData[i];
    // Имитация пробоя
    controllerData.flags &= 0xfe;
    if(++demoData[i] > uSpark + i + rand() % 15) {
        controllerData.flags |= 1;
        demoData[i] -= 3 + rand() % 9;
    }
    // Проверка Пуск/ Стоп
    if(!(status & (1 << i))) {
        demoData[i] = 7;
        controllerData.flags |= 0x80;
    } else
        controllerData.flags &= 0x7f;

    controllerData.u = demoData[i];

}

void Channel::makeIfilter(int u)
{
    controllerData.i = u > startCoronation ? (unsigned char)(u * u / scale) : 0;
}


void Channel::simulateData()
{
    const int maxTakts = 50;
    for(unsigned int i = 0; ; i++) {
        i %= maxTakts;
        controllerData.field=i/10 +1;

        int tact = i % 10;

        if (tact==1)
            makeUfilter(i/10);

        if (tact==2)
            makeIfilter(demoData[i/10]);

        if (tact==4) {
            if(rand() % 7 ) {
                controllerData.shake = 0;
                controllerData.errshake = 0;
            }
            else
                controllerData.shake = 1;
        }

        if (tact==9) {
            controllerData.err = 0;
            emit send(controllerData);

            if(!Channel::queueCommand.isEmpty())   {
               command = Channel::queueCommand.dequeue();    // nnnn cmnd

                if((command & 0xf) == powerOn ) {
                   status |= 1 << (command>>4);
                }
                if((command & 0xf) == powerOff )  {
                    status &= 0xff ^ 1 << (command>>4);
                }
            }
        }

        QThread::msleep(10);
    }
}

