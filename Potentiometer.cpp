#include <arduino.h>
#include "Potentiometer.h"

Potentiometer::Potentiometer(uint8_t pin) : _pin(pin)
{
    pinMode(pin, INPUT);
    _value = analogRead(_pin);
}

void Potentiometer::peek()
{
    int raw = ravg(analogRead(_pin));
    uint8_t mapped = map(raw, 0, 1024, _min, _max + 1);
    if (mapped != _value && _onChange != NULL)
    {
        _onChange(_value, mapped);
        _value = mapped;
    }
}

void Potentiometer::setCallback(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max)
{
    _onChange = onChange;
    _min = min;
    _max = max;
}

int Potentiometer::ravg(int x)
{
    _ravg_sum -= _ravg_buffer[_ravg_idx];
    _ravg_buffer[_ravg_idx % RAVG_BUFFER_SIZE] = x;
    _ravg_sum += _ravg_buffer[_ravg_idx % RAVG_BUFFER_SIZE];
    _ravg_idx++;
    _ravg_idx %= RAVG_BUFFER_SIZE;
    if (_ravg_count < RAVG_BUFFER_SIZE) _ravg_count++;
    return _ravg_sum / _ravg_count;
}