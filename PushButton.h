#pragma once

#include <Arduino.h>
#include "BtnHandler.h"

class PushButton
{
private:
    uint8_t _pin;
    unsigned long _lastClick = 0;
    bool _clicking = false;
    BtnHandler *_callback = NULL;
public:
    PushButton(uint8_t pin);
    void peek();
    void setCallback(BtnHandler &callback);
};