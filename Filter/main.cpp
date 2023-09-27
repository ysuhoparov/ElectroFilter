#include "mainwindow.h"
#include <QApplication>

//uint Channel::status =127;
QQueue<unsigned char> Channel::queueCommand;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
