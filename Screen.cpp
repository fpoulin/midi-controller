#define ARDUINO 1000
#include "LedControl.h"
#include "Screen.h"

LedControl dmt1 = LedControl(11, 9, 10, 4);
LedControl dmt2 = LedControl(8, 6, 7, 4);

unsigned char trigs[8];

Screen::Screen()
{
    trigs[0] = r(0b00000000);
    trigs[1] = r(0b01100110);
    trigs[2] = r(0b01100110);
    trigs[3] = r(0b00000000);
    trigs[4] = r(0b00011000);
    trigs[5] = r(0b00011000);
    trigs[6] = r(0b01000010);
    trigs[7] = r(0b00111100);

    // init screen
    for (int address = 0; address < dmt1.getDeviceCount(); address++)
    {
        dmt1.shutdown(address, false);
        dmt1.setIntensity(address, 0);
        dmt1.clearDisplay(address);
    }

    for (int address = 0; address < dmt2.getDeviceCount(); address++)
    {
        dmt2.shutdown(address, false);
        dmt2.setIntensity(address, 0);
        dmt2.clearDisplay(address);
    }
}

void Screen::display(int step)
{
    LedControl dmt = step < 32 ? dmt1 : dmt2;
    int bar = step % 32 / 8;
    int col = step % 8;

    for (int row = 0; row < 8; row++)
    {
        byte leds = trigs[7 - row]; // swap row vertically ...
        leds = leds | 0x1 << col;
        dmt.setRow(bar, row, leds);
    }
}

void Screen::clear(int step)
{
    LedControl dmt = step < 32 ? dmt1 : dmt2;
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