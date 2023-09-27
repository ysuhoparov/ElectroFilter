#ifndef REPORT_H
#define REPORT_H

#include <QDialog>
#include <QtWidgets>
#include <QDateTime>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QPushButton>
#include "qboxlayout.h"
#include "qtableview.h"

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport>
#endif

class Report : public QDialog
{
    Q_OBJECT

    void preview();

    QVBoxLayout* tableLay;
    QTableView* tableView;
    QSqlQueryModel * model;

    QDialogButtonBox* buttonBox;
    QPushButton* printButton;
    QPushButton* closeButton;

    QString title;

    QPrinter* printer=nullptr;

public:
    explicit Report();
    ~Report();

    void showVoltage(const QDateTime&);
    void showCurrentVoltage();
    void showMaintenance();
    void showRepairs();

public slots:

    void print();

};

#endif // REPORT_H
