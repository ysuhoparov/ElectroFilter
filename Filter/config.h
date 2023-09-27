#ifndef CONFIG_H
#define CONFIG_H

#include <QFile>
#include <QXmlStreamReader>

class Config
{
    int zones = 4;
    static const int maxZones = 8;
    int power[maxZones]{1,1,1,1,1,1,1,1};

    void setPower(QXmlStreamReader& xml);

public:
    Config(QString filePath);
    int getZones() const ;
    int getPower(int) const ;

    QString name;
    bool success;
    QString error;

};

#endif // CONFIG_H
