#pragma once

#include "Screen.h"
#include "SplashCallback.h"

class Splash
{
private:
    Screen &_screen;
    unsigned int _frame = 0;
    bool _playingPicto = false;
    bool _showingNumber = false;
    SplashCallback *_onFinish;

    uint8_t _pictoId;
    uint8_t _numberId;
    uint8_t _bitmap;
    uint8_t _buffer[5];
    float _animPercent;

    uint8_t getPosXShifted();

public:
    Splash(Screen &screen);
    bool isPlaying();
    void playPicto(uint8_t splashPictoId, SplashCallback &onFinish);
    void showNumber(uint8_t number, SplashCallback &onFinish); // 1-16
    void loop();
};