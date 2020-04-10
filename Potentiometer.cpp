#include "Potentiometer.h"
#include <arduino.h>

#define DEBOUNCE_TIME 500
#define EMA_ALPHA 0.3

Potentiometer::Potentiometer(uint8_t pin, uint8_t calibrationMin, uint8_t calibrationMax) : _pin(pin), _calibrationMin(calibrationMin), _calibrationMax(calibrationMax)
{
    pinMode(pin, INPUT);
    this->_value = analogRead(this->_pin);
}

void Potentiometer::peek()
{
    int raw = analogRead(this->_pin);
    int filtered = (EMA_ALPHA * raw) + ((1 - EMA_ALPHA) * this->_value);
    if (filtered != this->_value)
    {
        this->_onChange(this->_value, filtered);
        this->_value = filtered;
    }
}

void Potentiometer::setCallback(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max)
{
    this->_onChange = onChange;
}