#include "mainwindow.h"
#include "qtsimulator_lcd.h"
#include <iostream>

QtSimulator_LCD::QtSimulator_LCD(MainWindow * mainWindow_ref)
{
    this->mainWindow_ref = mainWindow_ref;

    this->mainWindow_ref->show();



    for (unsigned int i = 0; i < 1024; i++)
    {
        if (i == 0){
            LCDDataBuffer[i] = 0x03;
        }

        if (i == 128){
            LCDDataBuffer[i] = 0xff;
        }

        if (i == 1023){
            LCDDataBuffer[i] = 0xf0;
        }

        std::cout << i << ": " << LCDDataBuffer[i] << std::endl;
    }


    this->printBuffer(this->LCDDataBuffer);
}


void QtSimulator_LCD::printBuffer(uint8_t * const displayBuffer)
{
    this->mainWindow_ref->DisplayAccordingToBuffer(displayBuffer);
}
