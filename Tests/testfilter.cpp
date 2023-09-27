
#include <QTest>
#include "MVC/model.cpp"


class TestFilter: public QObject
{
    Q_OBJECT

    Model model;

private slots:
    void incode();
    void decode();
    void incodeFull();
    void incodeFull_data();

};


void TestFilter::incode()
{
    NetInfo nt{1, 0x55, 0xaa, 0, 0x81, 0x10, 0xa0, 0x50};
    QCOMPARE(model.incode(nt), (quint64)0x50a01081aa55);
}


void TestFilter::decode()
{
    NetInfo nt = model.decode((quint64)0x50a01081aa55);
    QCOMPARE(nt.u, 85);
    QCOMPARE(nt.i, 0xaa);
    QCOMPARE(nt.flags, 0x81);
    QCOMPARE(nt.shake, 0xa0);
}


void TestFilter::incodeFull()
{
    QFETCH(quint64, indata);
    QFETCH(quint64, result);

    QCOMPARE(model.incode(model.decode(indata)), result);
}

void TestFilter::incodeFull_data()
{
    QTest::addColumn<quint64>("indata");
    QTest::addColumn<quint64>("result");

    QTest::newRow("0 kV") << (quint64)0 << (quint64)0;
    QTest::newRow("U=37") << (quint64)0x50a010800a25 << (quint64)0x50a010800a25;
    QTest::newRow("U=50") << (quint64)0x203040840a32 << (quint64)0x203040840a32;
    QTest::newRow("U=86") << (quint64)0x102050831a56 << (quint64)0x102050831a56;
}



QTEST_MAIN(TestFilter)
#include "testfilter.moc"

