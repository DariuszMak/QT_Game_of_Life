#ifndef QTSIMULATOR_LCD_H
#define QTSIMULATOR_LCD_H
#include "mainwindow.h"


class QtSimulator_LCD
{
public:
    MainWindow * mainWindow_ref;
    QtSimulator_LCD(MainWindow * mainWindow_ref);
private:

    void printBuffer(uint8_t * const);
    uint8_t LCDDataBuffer[1024] { 0 };
};

#endif // QTSIMULATOR_LCD_H
