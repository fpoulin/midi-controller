#include "Potentiometer.h"

Potentiometer::Potentiometer(uint8_t pin) : _pin(pin)
{
    pinMode(pin, INPUT);
    _value = analogRead(_pin);
}

void Potentiometer::peek()
{
    if(_callback == NULL) return;

    int raw = ravg(analogRead(_pin));
    uint8_t mapped = map(raw, 0, 1024, _callback->minValue, _callback->maxValue + 1);
    if (mapped != _value)
    {
        _callback->onChange(_value, mapped);
        _value = mapped;
    }
}

void Potentiometer::setCallback(PotHandler &callback)
{
    _callback = &callback;
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