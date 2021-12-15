#ifndef QTSIMULATOR_LCD_H
#define QTSIMULATOR_LCD_H

#include "mainwindow.h"
#include "display.h"

#ifndef DISPLAY_COLUMNS
#define DISPLAY_COLUMNS 128
#endif
#ifndef DISPLAY_PAGES
#define DISPLAY_PAGES 8
#endif

#ifndef DISPLAY_ROWS
#define DISPLAY_ROWS (DISPLAY_PAGES * 8)
#endif

#define DISPLAY_BUFFER_SIZE (DISPLAY_COLUMNS * DISPLAY_PAGES)

class QtSimulator_LCD : public display
{
public:
    MainWindow * mainWindow_ref;
    QtSimulator_LCD() = delete;
    ~QtSimulator_LCD() = default;
    QtSimulator_LCD(MainWindow * mainWindow_ref);

    uint8_t font_ASCII;

    uint16_t getDisplayBufferPosition(uint8_t page, uint8_t column);
    uint16_t modify_buffer(unsigned char *target_buffer, char *input_text);
    void renderText(char *inputText, uint8_t page, uint8_t column);
    uint16_t create_text_buff(unsigned char *target_buffer, char *input_text);

    void printBuffer(uint8_t * const);

    void initialize_function();

private:
    uint8_t LCDDataBuffer[1024] { 0 };
};

#endif // QTSIMULATOR_LCD_H
