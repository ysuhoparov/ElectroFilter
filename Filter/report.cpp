#include "report.h"
#include "printview.h"


Report::Report() : QDialog{}
{
    //tableWindow = new QWidget;
    tableLay = new QVBoxLayout();
    tableView = new QTableView;
    model = new QSqlQueryModel;


    buttonBox = new QDialogButtonBox;
    printButton = buttonBox->addButton("Print", QDialogButtonBox::ActionRole);
    closeButton = buttonBox->addButton(QDialogButtonBox::Close);

    connect(printButton, &QPushButton::clicked, this, &Report::print);
    connect(closeButton, &QPushButton::clicked, this, &Report::close);

}

Report::~Report()
{

    delete model;
    if(printer) delete printer;
}


void Report::preview()
{
    tableView->setModel(model);

    tableView->resizeColumnsToContents();
    tableLay->addWidget(tableView);
    tableLay->addWidget(buttonBox);

//    tableWindow->show();

   setLayout(tableLay);
   setWindowTitle(title);
   show();
}

void Report::showCurrentVoltage()
{
    model->setQuery("select STRFTIME('%H:%M:%S', timerec) as Время, field1%256 as U_поля_1, field1/256%256 as I_поля_1, "
                    "field2 % 256 as U_поля_2, field2 / 256 % 256 as I_поля_2, "
                    "field3 % 256 as U_поля_3, field3 / 256 % 256 as I_поля_3, "
                    "field4 % 256 as U_поля_4, field4 / 256 % 256 as I_поля_4 "
                    "from history order by id desc LIMIT 32");

    resize(720,640);
    title = "Текущие параметры питания полей фильтра";

    preview();
}

void Report::showVoltage(const QDateTime& reportTime)
{
    QSqlQuery query;
    query.prepare("select STRFTIME('%H:%M:%S', timerec) as Время, field1%256 as U_поля_1, field1/256%256 as I_поля_1, "
                  "field2 % 256 as U_поля_2, field2 / 256 % 256 as I_поля_2, "
                  "field3 % 256 as U_поля_3, field3 / 256 % 256 as I_поля_3, "
                  "field4 % 256 as U_поля_4, field4 / 256 % 256 as I_поля_4 "
                  "from history where timerec <= :rtime order by id desc LIMIT 32");
    query.bindValue(":rtime", reportTime);
    query.exec();

    model->setQuery(query);

    resize(800,640);
    title ="Параметры питания полей фильтра на " + reportTime.toString("dd.MM.yyyy hh:mm:ss");

    preview();
}

void Report::showMaintenance()
{
    model->setQuery("select services.Id as №, STRFTIME('%d.%m.%Y', date) as Дата, "
                    "field as Поле, content as Содержание, "
                    "equipment as Запчасть, employee as Исполнитель "
                    "from services, employees, equipments "
                    "where services.employeeId = employees.id "
                    "and services.equipmentId = equipments.id ");

    resize(900,400);
    title ="Ведомость технического обслуживания";

    preview();
}

void Report::showRepairs()
{
    model->setQuery("select repairs.Id as №, STRFTIME('%d.%m.%Y', date) as Дата, "
                    "field as Поле, content as Содержание, "
                    "spare as Запчасть, employee as Исполнитель "
                    "from repairs, employees, spares "
                    "where repairs.employeeId = employees.id "
                    "and repairs.spareId = spares.id ");

    resize(900,400);
    title ="Ведомость текущего ремонта";

    preview();
}



void Report::print()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printpreviewdialog)

    int rows = tableView->model()->rowCount();
    int columns = model->columnCount();

    QString html = "<!DOCTYPE html> \n <html lang=\"ru\"> <head> \n \
                   <meta charset=\"utf-8\"> </head> <body style=\"font-size:12pt\">";

    html += "<div align=\"center\" valign = \"sub\" >";
    html += "<br><H1 >" + title + "</H1>";

    html += "<table cellspacing=16 >\n";
    html += "<thead> <tr>";
    for(int column = 0; column < columns; ++column)
        html += QString("<th>%1</th>").arg(model->headerData(column,Qt::Horizontal).toString());
    html += "</tr> </thead>";

    for(int row = 0; row < rows; ++row){
        html += "<tr>";
        for(int column = 0; column < columns; ++column) {
            QString data = model->data(model->index(row,column)).toString().simplified();
            html += QString("<td align=\"center\">%1</td>").arg((!data.isEmpty()) ? data : QString ("&nbsp;"));
        }
        html += "</tr>";
    }
    html += "</table> \n </div> \n </body>";

    printer = new QPrinter(QPrinter::ScreenResolution);
    QPrintPreviewDialog dialog(printer);
    PrintView view;
    view.insertHtml(html);
    connect(&dialog, &QPrintPreviewDialog::paintRequested, &view, &PrintView::print);
    dialog.exec();

#endif
}
