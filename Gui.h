#include "Screen.h"
#include "State.h"

#pragma once

class Gui
{
private:
    Screen _screen;
    State &_state;
    uint8_t _trigs[8];
    uint8_t _lastStep = 0;
    uint8_t _cursorX = 0;
    uint8_t _cursorY = 0;
    unsigned long _lastRepaint = 0;

    void redrawChords();
    void redrawChannel(uint8_t channel);
    void redrawAt(uint8_t y);

public:
    Gui(State &state);
    void loop();
    void renderStep(uint8_t step);
    void moveCursorX(uint8_t n);
    void moveCursorY(uint8_t n);
    void clickCursor(bool toggle);
    void reset();
};