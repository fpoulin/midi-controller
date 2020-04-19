#include "Screen.h"

#pragma once

class Splash
{
private:
    Screen &_screen;
    unsigned int _frame = 0;
    bool _playing = false;
    bool _finished = false;

public:
    Splash(Screen &screen);
    bool isPlaying();
    bool justFinished();
    void play();
    void loop();
};