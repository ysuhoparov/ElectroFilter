#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "field.h"
#include "config.h"
#include "MVC/model.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QAction;
class QLabel;
class QMenu;
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;

    int count=0;
    int zones = 4;
    Field **fields;
    Config *config;

    void paintEvent(QPaintEvent*) override;

private slots:

    void spareCatalog();
    void roleCatalog();
    void employeeCatalog();
    void kindCatalog();;
    void equipmentCatalog();

    void updateConfig();

    void operativeLog();
    void repairLog();
    void serviceLog();

    void showCurrentVoltage();
    void selectTime();
    void showMaintenance();
    void showRepairs();

    void about();
    void aboutFilter();

    void refresh(NetInfo);

private:

    Model* model;

    void createActions();
    void createMenus();

    QMenu *settingMenu;
    QMenu *logMenu;
    QMenu *reportMenu;
    QMenu *helpMenu;

    QAction *spareAct;
    QAction *roleAct;
    QAction *employeeAct;
    QAction *typeAct;
    QAction *equipmentAct;

    QAction *updateConfigAct;
    QAction *exitAct;

    QAction *operativeLogAct;
    QAction *repairLogAct;
    QAction *serviceLogAct;

    QAction *paramAct;
    QAction *selectAct;
    QAction *serviceAct;
    QAction *repairAct;

    QAction *aboutAct;
    QAction *aboutFilterAct;

signals:
    void sendcmd(unsigned int);
};
#endif // MAINWINDOW_H
