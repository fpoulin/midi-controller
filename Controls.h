#include "PushButton.h"
#include "Potentiometer.h"

#pragma once

class Controls
{
private:
    unsigned long _lastPeek = 0;
    PushButton &_btn1;
    PushButton &_btn2;
    PushButton &_btn3;
    Potentiometer &_pot1;
    Potentiometer &_pot2;
    Potentiometer &_pot3;
    Potentiometer &_pot4;
public:
    Controls(PushButton &btn1, PushButton &btn2, PushButton &btn3, Potentiometer &pot1, Potentiometer &pot2, Potentiometer &pot3, Potentiometer &pot4);
    void loop();
    void setHandleBtn1(void (*onClick)(void));
    void setHandleBtn2(void (*onClick)(void));
    void setHandleBtn3(void (*onClick)(void));
    void setHandlePot1(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max);
    void setHandlePot2(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max);
    void setHandlePot3(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max);
    void setHandlePot4(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max);
};