#include "model.h"
#include "field.h"

#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>

Model::Model()
{
    // Подключение к СуБД
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost1");
    db.setDatabaseName("db.sqlite3");
    db.setUserName("");
    db.setPassword("");

    if(db.open())
        isOpen = true;
}


void Model::store(Field** fields, const int zones) const
{
    static int lastsec=QDateTime::currentDateTime().time().second();

    if(!isOpen) return;

    QDateTime cdt = QDateTime::currentDateTime();
    if(lastsec != cdt.time().second()) {
        lastsec = cdt.time().second();
        QSqlQuery query;
        query.prepare("INSERT INTO history ( timerec, field1, field2, field3, field4 ) "
                      "VALUES (:timerec, :f1, :f2, :f3, :f4)");
        query.bindValue(":timerec", cdt);

        query.bindValue(":f1", incode(fields[0]->data));
        query.bindValue(":f2", incode(fields[1]->data));

        query.bindValue(":f3", incode(fields[2]->data));
        if(zones > 3)
            query.bindValue(":f4", incode(fields[3]->data));

        query.exec();
   //         if(query.lastError().text()!="")
    //            statusBar()->showMessage(query.lastError().text());
        }

}


quint64 Model::incode(const NetInfo& nt) const
{
        //    quint64 uif = nt.u + (nt.i << 8) + (nt.flags << 16) + ((quint64) nt.err << 24);
        //    quint64 rgn = ((quint64)nt.shake << 32) + ((quint64)nt.errshake << 40);

        quint64 encodedData = (quint64)nt.errshake;
        encodedData <<= 8;

        encodedData += (quint64)nt.shake;
        encodedData <<= 8;

        encodedData += (quint64)nt.err;
        encodedData <<= 8;

        encodedData += (quint64)nt.flags;
        encodedData <<= 8;

        encodedData += (quint64)nt.i;
        encodedData <<= 8;

        encodedData += (quint64)nt.u;

        return encodedData;
}


NetInfo Model::decode(quint64 data)
{
        NetInfo nt;
        nt.u = (unsigned char) (data & 255);
        data >>= 8;
        nt.i = (unsigned char) (data & 255);
        data >>= 8;
        nt.flags = (unsigned char) (data & 255);
        data >>= 8;
        nt.err = (unsigned char) (data & 255);

        data >>= 8;
        nt.shake = (unsigned char) (data & 255);
        data >>= 8;
        nt.errshake = (unsigned char) (data & 255);

        return nt;

}
