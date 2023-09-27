#include "datedialog.h"
#include "report.h"

DateDialog::DateDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

}

void DateDialog::on_buttonBox_clicked()
{
    const QDateTime& dt = (ui.dateTimeEdit->dateTime());
    Report* rp = new Report;
    rp->showVoltage(dt);
}

void DateDialog::on_calendarWidget_clicked(const QDate &date)
{
        ui.dateTimeEdit->setDate(date);
        ui.dateTimeEdit->setTime(QTime::currentTime());
}

