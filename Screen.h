#include <LedControl.h>

#pragma once

class Screen
{
private:
    LedControl _dmt1;
    uint8_t _dmt1RowsCur[8][4]; // 8 rows over 4 columns
    uint8_t _dmt1RowsNext[8][4];

    LedControl _dmt2;
    uint8_t _dmt2RowsCur[8][4];
    uint8_t _dmt2RowsNext[8][4];

    uint8_t _bitmap;

public:
    Screen();
    void setPixel(uint8_t x, uint8_t y, bool state);
    bool getPixel(uint8_t x, uint8_t y);
    void repaint();
    void clear();
};