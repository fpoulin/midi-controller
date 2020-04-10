#pragma once

#include <Arduino.h>

class PushButton
{
private:
    uint8_t _pin;
    unsigned long _lastClick = 0;
    bool _clicking = false;
    void (*_onClick)(void) = NULL;
public:
    PushButton(uint8_t pin);
    void peek();
    void setHandleBtn(void (*onClick)(void));
};