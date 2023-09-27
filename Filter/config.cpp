#include "config.h"

Config::Config(QString filePath)
{
    error = "";

    QFile* file = new QFile(filePath);

    if (file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        QXmlStreamReader xml(file);

        while (!xml.atEnd() && !xml.hasError()) {
            QXmlStreamReader::TokenType token = xml.readNext();

            if (token == QXmlStreamReader::StartElement) {

                if (xml.name() == QString("zones")) {
                    zones = xml.readElementText().toInt();
                    continue;
                }

               if (xml.name() == QString("name")) {
                    name = xml.readElementText();
                    continue;
                }

                setPower(xml);
            }
        }

        if(xml.hasError()) {
            error = xml.errorString();
            success = false;
        }
        else
            success = true;

        delete file;

    }
}


void Config::setPower(QXmlStreamReader& xml)
{
    for(int i =1; i<= zones; i++) {
        if (xml.name() == QString("p" +QString::number(i))) {
            power[i-1] = xml.readElementText().toInt();
        }
    }
}



int Config::getPower(int i) const {
        return power[i];
}



int Config::getZones() const {
        return zones;
}

