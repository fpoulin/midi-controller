#include "Screen.h"

#pragma once

class Splash
{
private:
    Screen &_screen;
    unsigned int _frame = 0;
    bool _playing = false;
    bool _finished = false;

    uint8_t _pictoId;
    uint8_t _bitmap;
    float _animPercent;

    uint8_t getPosX();

public:
    Splash(Screen &screen);
    bool isPlaying();
    bool justFinished();
    void play(uint8_t splashPictoId);
    void loop();
};