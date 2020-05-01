#include "Screen.h"
#include "SplashCallback.h"

#pragma once

class Splash
{
private:
    Screen &_screen;
    unsigned int _frame = 0;
    bool _playing = false;
    SplashCallback *_onFinish;

    uint8_t _pictoId;
    uint8_t _bitmap;
    float _animPercent;

    uint8_t getPosXShifted();

public:
    Splash(Screen &screen);
    bool isPlaying();
    void play(uint8_t splashPictoId, SplashCallback &onFinish);
    void loop();
};