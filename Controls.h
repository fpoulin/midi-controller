#include "PushButton.h"
#include "Potentiometer.h"

#pragma once

class Controls
{
private:
    unsigned long _lastPeek = 0;
    PushButton _btn1;
    PushButton _btn2;
    PushButton _btn3;
    Potentiometer _rot1;
    Potentiometer _rot2;
    Potentiometer _rot3;
    Potentiometer _rot4;
    Potentiometer _lin;
public:
    Controls(PushButton btn1, PushButton btn2, PushButton btn3, Potentiometer rot1, Potentiometer rot2, Potentiometer rot3, Potentiometer rot4, Potentiometer lin);
    void loop();
    void setHandleBtn1(void (*onClick)(void));
    void setHandleBtn2(void (*onClick)(void));
    void setHandleBtn3(void (*onClick)(void));
    void setHandleRotary1(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max);
    void setHandleRotary2(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max);
    void setHandleRotary3(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max);
    void setHandleRotary4(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max);
    void setHandleLinear1(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max);
};