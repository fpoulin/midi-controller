#include <LedControl.h>
#include "State.h"

#pragma once

class Screen
{
private:
    LedControl _dmt1;
    LedControl _dmt2;
    unsigned char _trigs[8];
    int _lastStep = 0;

public:
    Screen();
    void init(State &state);
    void moveCursor(int step);
    void clear(int step);

private:
    unsigned char r(unsigned char b);
};