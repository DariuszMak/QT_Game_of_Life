#ifndef QTSIMULATOR_LCD_H
#define QTSIMULATOR_LCD_H
#include "mainwindow.h"


class QtSimulator_LCD
{
public:
    MainWindow * mainWindow_ref;
    QtSimulator_LCD(MainWindow * mainWindow_ref);
};

#endif // QTSIMULATOR_LCD_H
