#pragma once

#include "PushButton.h"
#include "Potentiometer.h"

class Controls
{
private:
    unsigned long _lastPeek = 0;

public:
    Controls();
    PushButton btn1;
    PushButton btn2;
    PushButton btn3;
    Potentiometer pot1;
    Potentiometer pot2;
    Potentiometer pot3;
    Potentiometer pot4;
    void loop();
};