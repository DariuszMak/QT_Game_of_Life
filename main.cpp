#include "mainwindow.h"
#include "qtsimulator_lcd.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.show();

    QtSimulator_LCD qtsimulator_lcd(&w);

    return a.exec();
}
