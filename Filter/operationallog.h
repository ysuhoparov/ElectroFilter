#ifndef OPERATIONALLOG_H
#define OPERATIONALLOG_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include "ui_operationalLog.h"

class OperationalLog : public QDialog
{
    Q_OBJECT

    void refresh();
    QSqlQueryModel* model;
    QSqlQueryModel* employeeModel;

    QSqlQuery query;
    int employeeId;
    int editableId;
    bool isEditable;

public:
    explicit OperationalLog(QWidget *parent = nullptr);
    ~OperationalLog();

    Ui::operationalLog ui;

signals:

private slots:
    void on_startDate_userDateChanged();
    void on_savebtnBox_accepted();
    void on_savebtnBox_rejected();
    void on_editBtn_clicked();

  //  void on_employeeBox_currentIndexChanged(int index);
};

#endif // OPERATIONALLOG_H
