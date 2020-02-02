#include "Screen.h"
#include "State.h"

#pragma once

class Gui
{
private:
    Screen _screen;
    State _state;
    uint8_t _trigs[8];
    uint8_t _lastStep = 0;

public:
    Gui(State &state);
    void moveToStep(uint8_t step);
    void reset();

private:
    
};