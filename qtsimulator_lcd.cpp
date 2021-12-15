#include "mainwindow.h"
#include "qtsimulator_lcd.h"

QtSimulator_LCD::QtSimulator_LCD(MainWindow * mainWindow_ref)
{
    this->mainWindow_ref = mainWindow_ref;

    this->mainWindow_ref->show();
}
