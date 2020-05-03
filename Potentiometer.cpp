#include "Potentiometer.h"

Potentiometer::Potentiometer(uint8_t pin) : _pin(pin)
{
    pinMode(pin, INPUT);
    _value = analogRead(_pin);
}

void Potentiometer::peek()
{
    if (_callback == NULL) return;

    int raw = ravg(analogRead(_pin));
    uint8_t mapped = map(raw, 0, 1024, _callback->minValue, _callback->maxValue + 1);
    if (mapped != _value)
    {
        _value = mapped;
        
        if (_ravg_count == RAVG_BUFFER_SIZE)
        {
            _callback->onChange(_value, mapped);
        }
    }
}

void Potentiometer::setCallback(PotHandler &callback)
{
    _callback = &callback;
    resetRavg();
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

void Potentiometer::resetRavg() 
{
    for (uint8_t i = 0; i < RAVG_BUFFER_SIZE; i++)
    {
        _ravg_buffer[i] = 0;
    }
    
    _ravg_idx = 0;
    _ravg_sum = 0;
    _ravg_count = 0;
}