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

    uint8_t font_ASCII;

    void printBuffer(uint8_t * const);
    void printSimpleText(uint8_t * const, char *);

    void initialize_function();

private:
    uint8_t LCDDataBuffer[1024] { 0 };
};

#endif // QTSIMULATOR_LCD_H
