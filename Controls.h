#pragma once

#include "PushButton.h"
#include "Potentiometer.h"
#include "PotHandler.h"

class Controls
{
private:
    unsigned long _lastPeek = 0;
    PushButton &_btn1;
    PushButton &_btn2;
    PushButton &_btn3;
public:
    Controls(PushButton &btn1, PushButton &btn2, PushButton &btn3);
    
    Potentiometer pot1;
    Potentiometer pot2;
    Potentiometer pot3;
    Potentiometer pot4;

    void loop();
    void setHandleBtn1(void (*onClick)(void));
    void setHandleBtn2(void (*onClick)(void));
    void setHandleBtn3(void (*onClick)(void));
};