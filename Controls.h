#include "PushButton.h"

#pragma once

class Controls
{
private:
    PushButton _btn1; // push 1
    PushButton _btn2; // push 2
    PushButton _btn3; // push 3
    void (*_onChangeKnob1)(uint8_t oldValue, uint8_t newValue);
    void (*_onChangeKnob2)(uint8_t oldValue, uint8_t newValue);
    void (*_onChangeKnob3)(uint8_t oldValue, uint8_t newValue);
    void (*_onChangeKnob4)(uint8_t oldValue, uint8_t newValue);
    void (*_onChangeLinear)(uint8_t oldValue, uint8_t newValue);
public:
    Controls(uint8_t pinBtn1, uint8_t pinBtn2, uint8_t pinBtn3);
    void loop();
    void setHandleBtn1(void (*onClick)(void));
    void setHandleBtn2(void (*onClick)(void));
    void setHandleBtn3(void (*onClick)(void));
    void setHandleKnob1(void (*onChange)(uint8_t oldValue, uint8_t newValue));
    void setHandleKnob2(void (*onChange)(uint8_t oldValue, uint8_t newValue));
    void setHandleKnob3(void (*onChange)(uint8_t oldValue, uint8_t newValue));
    void setHandleKnob4(void (*onChange)(uint8_t oldValue, uint8_t newValue));
    void setHandleLinear(void (*onChange)(uint8_t oldValue, uint8_t newValue));
};