#pragma once

#include <Arduino.h>

class Potentiometer
{
private:
    uint8_t _pin;
    uint8_t _calibrationMin;
    uint8_t _calibrationMax;
    int _value = 0;
    void (*_onChange)(uint8_t oldValue, uint8_t newValue) = NULL;
public:
    Potentiometer(uint8_t pin, uint8_t calibrationMin, uint8_t calibrationMax);
    void peek();
    void setCallback(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max);
};