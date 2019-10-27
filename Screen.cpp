#include <LedControl.h>
#include "Screen.h"

Screen::Screen() : _dmt1(LedControl(11, 9, 10, 4)), _dmt2(LedControl(8, 6, 7, 4))
{
    for (byte i = 0; i < 8; i++)
    {
        this->_trigs[i] = 0;
    }

    // init screen
    for (int address = 0; address < 4; address++)
    {
        this->_dmt1.shutdown(address, false);
        this->_dmt1.setIntensity(address, 0);
        this->_dmt1.clearDisplay(address);

        this->_dmt2.shutdown(address, false);
        this->_dmt2.setIntensity(address, 0);
        this->_dmt2.clearDisplay(address);
    }
}

void Screen::moveCursor(int step)
{
    clear(this->_lastStep);
    
    step = step % 64;

    LedControl dmt = step < 32 ? this->_dmt1 : this->_dmt2;
    int bar = step % 32 / 8;
    int col = step % 8;

    for (int row = 0; row < 8; row++)
    {
        byte leds = this->_trigs[7 - row]; // swap row vertically ...
        leds = leds | 0x1 << col;
        dmt.setRow(bar, row, leds);
    }

    this->_lastStep = step;
}

void Screen::clear(int step)
{
    step = step % 64;

    LedControl dmt = step < 32 ? this->_dmt1 : this->_dmt2;
    int bar = step % 32 / 8;

    // clear the module
    for (int row = 0; row < 8; row++)
    {
        dmt.setRow(bar, row, 0);
    }
}

// swap col horizontally...
unsigned char Screen::r(unsigned char b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}