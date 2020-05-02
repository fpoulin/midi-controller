#include "Screen.h"

Screen::Screen() : _dmt1(LedControl(11, 9, 10, 4)), _dmt2(LedControl(8, 6, 7, 4))
{
    clear();
}

void Screen::setPixel(uint8_t x, uint8_t y, bool state)
{
    if (x < 0 || x > 31 || y < 0 || y > 15)
    {
        return;
    }

    // pick the right dmt
    uint8_t &row = y < 8
        ? _dmt1RowsNext[y][x / 8]
        : _dmt2RowsNext[y % 8][x / 8];

    // x=18 -> bitmap = 01000000 (swapped)
    _bitmap = 0x01 << (x % 8);
    if (state)
    {
        // add bit (row OR 01000000)
        row |= _bitmap;
    }
    else
    {
        // clear the bit (row AND 10111111)
        row &= ~_bitmap;
    }
}

bool Screen::getPixel(uint8_t x, uint8_t y)
{
    if (x < 0 || x > 31 || y < 0 || y > 15)
    {
        return false;
    }

    // pick the right dmt
    uint8_t row = y < 8
        ? _dmt1RowsCur[y][x / 8]
        : _dmt2RowsCur[y % 8][x / 8];

    // x=18 -> bitmap = 01000000 (swapped)
    _bitmap = 0x01 << (x % 8);
    return row & _bitmap;
}

void Screen::repaint()
{
    // find and apply changes selectively (bitwise diff, work per row)
    for (uint8_t i = 0; i < 8; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
            _bitmap = _dmt1RowsCur[i][j] ^ _dmt1RowsNext[i][j];
            if (_bitmap != 0)
            {
                _dmt1.setRow(j, 7 - i, _dmt1RowsNext[i][j]);
                _dmt1RowsCur[i][j] = _dmt1RowsNext[i][j];
            }

            _bitmap = _dmt2RowsCur[i][j] ^ _dmt2RowsNext[i][j];
            if (_bitmap != 0)
            {
                _dmt2.setRow(j, 7 - i, _dmt2RowsNext[i][j]);
                _dmt2RowsCur[i][j] = _dmt2RowsNext[i][j];
            }
        }
    }
}

void Screen::clear()
{
    for (uint8_t i = 0; i < 8; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
            _dmt1RowsCur[i][j] = 0;
            _dmt1RowsNext[i][j] = 0;
            _dmt2RowsCur[i][j] = 0;
            _dmt2RowsNext[i][j] = 0;
        }
    }

    // re-init screen
    for (int address = 0; address < 4; address++)
    {
        _dmt1.shutdown(address, false);
        _dmt1.setIntensity(address, 0);
        _dmt1.clearDisplay(address);

        _dmt2.shutdown(address, false);
        _dmt2.setIntensity(address, 0);
        _dmt2.clearDisplay(address);
    }
}