#ifndef QTSIMULATOR_LCD_H
#define QTSIMULATOR_LCD_H

#include "mainwindow.h"
#include "display.h"

class QtSimulator_LCD : public display
{
public:
    MainWindow * mainWindow_ref;
    QtSimulator_LCD() = delete;
    ~QtSimulator_LCD() = default;
    QtSimulator_LCD(MainWindow * mainWindow_ref);

    void printBuffer(uint8_t * const);

private:
    uint8_t LCDDataBuffer[1024] { 0 };
};

#endif // QTSIMULATOR_LCD_H
