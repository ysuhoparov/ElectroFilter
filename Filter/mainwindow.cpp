#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "enums.h"
#include "datedialog.h"
#include "report.h"
//#include "repair.h"
//#include "checkup.h"
//#include "spare.h"

#include <about.h>
#include "MVC/catalogview.h"
#include "MVC/catalogchoiceview.h"
#include "MVC/operativelogview.h"
#include "MVC/repairlogview.h"
#include <MVC/servicelogview.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    config = new Config("../../config.xml");
    zones = config->getZones();

    ui->setupUi(this);

    QWidget *widget = new QWidget;
    QWidget *topFiller = new QWidget;
    QWidget *bottomFiller = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topFiller);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    setWindowTitle(config->name);
    resize(1280, 720);
    createMenus();

    model = new Model;
    if(model->isOpen)
        statusBar()->showMessage("Db is open");

    if(!config->success)
        statusBar()->showMessage(config->error + " Config file wrong - Demo mode");

// Инициализация  полей фильтра
    fields = new Field*[zones];
    for(int i = 0; i < zones; i++) {
        fields[i] = new Field(this , i, zones);
        fields[i]->setPower(config->getPower(i));
    }

// Создание потока для канала связи с контроллерами полей электрофильтра
    QThread *thread= new QThread;
    Channel *channel = new Channel();

    channel->moveToThread(thread);
    connect(channel, SIGNAL(send(NetInfo)), this, SLOT(refresh(NetInfo)));
    connect(thread, SIGNAL(started()), channel, SLOT(simulateData()));
    thread->start();
}


MainWindow::~MainWindow()
{
    for(int i = 0; i < zones; i++)
        delete fields[i];
    delete fields;

    delete config;
    delete ui;
}

// Отображение полученной по каналу связи информации
void MainWindow::refresh(NetInfo data)
{
    if(data.field <= zones and data.field > 0) {
        fields[data.field-1]->refresh(data);
        model->store(fields, zones);
    }
}

// Дорисовка бункеров, входной и выходной зон фильтра
void MainWindow::paintEvent(QPaintEvent *)
{
    const int xbunker = 80;
    const int ybunker = 140;
    const int xchimney = 100;
    const int ychimney = 180;
    QPainter painter;
    painter.begin(this);
    for(int i =0; i < zones; i++) {
        auto f = fields[i]->frame;
        painter.drawLine(f->x(), f->y()+f->height(), f->x()+xbunker, f->y()+f->height() + ybunker);
        painter.drawLine(f->x()+f->width(), f->y()+f->height(),
                         f->x()+f->width()-xbunker, f->y()+f->height() + ybunker);
        painter.drawLine(f->x()+xbunker, f->y()+f->height() + ybunker,
                         f->x()+f->width()-xbunker, f->y()+f->height() + ybunker);
        if(!i) {
            painter.drawLine(f->x(), f->y(), f->x() - xchimney, f->y() +ychimney);
            painter.drawLine(f->x(), f->y()+f->height(), f->x()-xchimney, f->y()+f->height()-ychimney);
            painter.drawLine(f->x() - xchimney, f->y() +ychimney,
                             f->x() - xchimney, f->y()+f->height()-ychimney);
        }
        if(i == zones-1) {
            painter.drawLine(f->x()+f->width(), f->y(), f->x()+f->width()+xchimney, f->y() +ychimney);
            painter.drawLine(f->x()+f->width(), f->y()+f->height(),
                             f->x()+f->width()+xchimney, f->y()+f->height()-ychimney);
            painter.drawLine(f->x()+f->width()+xchimney, f->y()+f->height()-ychimney,
                             f->x()+f->width()+xchimney, f->y() +ychimney);
        }
    }
    painter.end();
}


void MainWindow::spareCatalog()
{
    CatalogView* catalog = new CatalogView((size_t)Catalogs::spare, this);
    catalog->open();
}

void MainWindow::roleCatalog()
{
    CatalogView* catalog = new CatalogView((size_t)Catalogs::role, this);
    catalog->open();
}

void MainWindow::employeeCatalog()
{
    CatalogView* catalog = new CatalogChoiceView((size_t)Catalogs::employee, this);
    catalog->open();
}

void MainWindow::kindCatalog()
{
    CatalogView* catalog = new CatalogView((size_t)Catalogs::kind, this);
    catalog->open();
}

void MainWindow::equipmentCatalog()
{
    CatalogView* catalog = new CatalogChoiceView((size_t)Catalogs::equipment, this);
    catalog->open();
}


void MainWindow::updateConfig()
{
    config = new (config) Config("../../config.xml");
    setWindowTitle(config->name);

    for(int i = 0; i < zones; i++)
        fields[i]->setPower(config->getPower(i));
}


void MainWindow::operativeLog()
{
    OperativeLogView* op = new OperativeLogView(this);
    op->open();
}

void MainWindow::repairLog()
{
    RepairLogView* sp = new RepairLogView(this);
    sp->open();
}

void MainWindow::serviceLog()
{
    ServiceLogView* sp = new ServiceLogView(this);
    sp->open();
}

void MainWindow::showCurrentVoltage()
{   Report* rp = new Report;
    rp->showCurrentVoltage();
}

void MainWindow::selectTime()
{
    DateDialog *dateDialog = new DateDialog(this);
    dateDialog->show();
}

void MainWindow::showMaintenance()
{   Report* rp = new Report;
    rp->showMaintenance();
}

void MainWindow::showRepairs()
{   Report* rp = new Report;
    rp->showRepairs();
}


void MainWindow::aboutFilter()
{
    QMessageBox::about(this, tr("About Filter"), ab.aboutFilter);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"), ab.about);
}


void MainWindow::createMenus()
{
    settingMenu = menuBar()->addMenu(tr("&Настройки"));
    logMenu = menuBar()->addMenu(tr("&Журналы"));
    reportMenu = menuBar()->addMenu(tr("&Отчеты"));
    helpMenu = menuBar()->addMenu(tr("&Справки"));

    spareAct = new QAction(tr("&Справочник запчастей"), this);
    spareAct->setStatusTip(tr("Ведение справочника запчастей"));
    connect(spareAct, &QAction::triggered, this, &MainWindow::spareCatalog);

    settingMenu->addAction(spareAct);

    roleAct = new QAction(tr("&Справочник ролей"), this);
    roleAct->setStatusTip(tr("Ведение справочника ролей работников"));
    connect(roleAct, &QAction::triggered, this, &MainWindow::roleCatalog);
    settingMenu->addSeparator();
    settingMenu->addAction(roleAct);

    employeeAct = new QAction(tr("&Справочник сотрудников"), this);
    employeeAct->setStatusTip(tr("Ведение справочника работников"));
    connect(employeeAct, &QAction::triggered, this, &MainWindow::employeeCatalog);
    settingMenu->addAction(employeeAct);

    typeAct = new QAction(tr("&Справочник видов оборудования"), this);
    typeAct->setStatusTip(tr("Ведение справочника видов оборудования"));
    connect(typeAct, &QAction::triggered, this, &MainWindow::kindCatalog);
    settingMenu->addSeparator();
    settingMenu->addAction(typeAct);

    equipmentAct = new QAction(tr("&Справочник оборудования"), this);
    equipmentAct->setStatusTip(tr("Ведение справочника оборудования"));
    connect(equipmentAct, &QAction::triggered, this, &MainWindow::equipmentCatalog);
    settingMenu->addAction(equipmentAct);


    updateConfigAct = new QAction(tr("&Обновить настройки"), this);
    updateConfigAct->setStatusTip(tr("Загрузить конфигурацию из файла"));
    connect(updateConfigAct, &QAction::triggered, this, &MainWindow::updateConfig);
    settingMenu->addSeparator();
    settingMenu->addAction(updateConfigAct);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);
    settingMenu->addAction(exitAct);


    operativeLogAct = new QAction(tr("&Оперативный журнал"), this);
    operativeLogAct->setStatusTip(tr("Ведение оперативного журнала"));
    connect(operativeLogAct, &QAction::triggered, this, &MainWindow::operativeLog);
    logMenu->addAction(operativeLogAct);

    serviceLogAct = new QAction(tr("&Журнал технического обслуживания"), this);
    serviceLogAct->setStatusTip(tr("Журнал учета технического обслуживания оборудования"));
    connect(serviceLogAct, &QAction::triggered, this, &MainWindow::serviceLog);
    logMenu->addAction(serviceLogAct);

    repairLogAct = new QAction(tr("&Журнал ремонта"), this);
    repairLogAct->setStatusTip(tr("Ведение журнала проведенных ремонтов"));
    connect(repairLogAct, &QAction::triggered, this, &MainWindow::repairLog);
    logMenu->addAction(repairLogAct);

    paramAct = new QAction(tr("&Текущие параметры питания"), this);
    paramAct->setStatusTip(tr("Текущие параметры питания фильтра"));
    connect(paramAct, &QAction::triggered, this, &MainWindow::showCurrentVoltage);
    reportMenu->addAction(paramAct);

    selectAct = new QAction(tr("&Параметры питания"), this);
    selectAct->setStatusTip(tr("Параметры питания ..."));
    connect(selectAct, &QAction::triggered, this, &MainWindow::selectTime);
    reportMenu->addAction(selectAct);

    serviceAct = new QAction(tr("&Техническое обслуживание"), this);
    serviceAct->setStatusTip(tr("Ведомость технического обслуживания"));
    connect(serviceAct, &QAction::triggered, this, &MainWindow::showMaintenance);
    reportMenu->addSeparator();
    reportMenu->addAction(serviceAct);

    repairAct = new QAction(tr("&Ремонтные работы"), this);
    repairAct->setStatusTip(tr("Ведомость текущего ремонта"));
    connect(repairAct, &QAction::triggered, this, &MainWindow::showRepairs);
    reportMenu->addAction(repairAct);


    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
    helpMenu->addAction(aboutAct);

    aboutFilterAct = new QAction(tr("&AboutFilter"), this);
    aboutFilterAct->setStatusTip(tr("Show the application's AboutFilter box"));
    connect(aboutFilterAct, &QAction::triggered, this, &MainWindow::aboutFilter);
    helpMenu->addAction(aboutFilterAct);
}



