#ifndef DISPLAY_H
#define DISPLAY_H
#include "stdint.h"

class display
{
public:
    display() = default;
    ~display() = default;

    display(uint16_t displayHeigh, uint16_t displayWidth);

    virtual void printBuffer(uint8_t* const displayBuffer) = 0;
};

#endif // DISPLAY_H
