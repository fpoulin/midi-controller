#include "Screen.h"
#include "State.h"
#include "Splash.h"

#pragma once

class Gui : private SplashCallback
{
private:
    Screen _screen;
    State &_state;
    uint8_t _trigs[8];
    uint8_t _lastStep = 0;
    uint8_t _cursorX = 0;
    uint8_t _cursorY = 0;
    Splash _splash;
    uint8_t _mode = 0;
    bool _cursorBlinkState = false;
    unsigned long _lastBlink = 0;
    unsigned long _lastRepaint = 0;

    uint8_t getStateDestination(); // 0:chords, 1: ch1 notes, 2:ch1 trigs, 3: ch2 notes, 4: ch2 trigs, 42: unmapped

public:
    Gui(State &state);
    void loop();

    void renderStep(uint8_t step);
    void redrawChords();
    void redrawChannel(uint8_t channel);
    void redrawAtCursorY();
    void redraw(bool resetScreen);
    
    void moveCursorX(uint8_t n);
    void moveCursorY(uint8_t n);
    void clickCursor();

    void switchMode(uint8_t mode);
    void onSplashEnd() override;

    void nudge(uint8_t amount, bool horizontal);
    void handleChordIn(uint8_t *chord, uint8_t nbNotes);
    void loopSteps();
};