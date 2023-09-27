#ifndef DATEDIALOG_H
#define DATEDIALOG_H

#include <QDialog>

#include "ui_datedialog.h"

class DateDialog : public QDialog
{
    Q_OBJECT

public:
    DateDialog(QWidget *parent = nullptr);

    Ui::DateDialog ui;

private slots:
    void on_buttonBox_clicked();
    void on_calendarWidget_clicked(const QDate &date);
};

#endif // DATEDIALOG_H
