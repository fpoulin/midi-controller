#include <arduino.h>
#include "Potentiometer.h"

Potentiometer::Potentiometer(uint8_t pin) : _pin(pin)
{
    pinMode(pin, INPUT);
    this->_value = analogRead(this->_pin);
}

void Potentiometer::peek()
{
    int raw = ravg(analogRead(this->_pin));
    uint8_t mapped = map(raw, 0, 1024, this->_min, this->_max + 1);
    if (mapped != this->_value && this->_onChange != NULL)
    {
        this->_onChange(this->_value, mapped);
        this->_value = mapped;
    }
}

void Potentiometer::setCallback(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max)
{
    this->_onChange = onChange;
    this->_min = min;
    this->_max = max;
}

int Potentiometer::ravg(int x)
{
    this->_ravg_sum -= this->_ravg_buffer[this->_ravg_idx];
    this->_ravg_buffer[this->_ravg_idx % RAVG_BUFFER_SIZE] = x;
    this->_ravg_sum += this->_ravg_buffer[this->_ravg_idx % RAVG_BUFFER_SIZE];
    this->_ravg_idx++;
    this->_ravg_idx %= RAVG_BUFFER_SIZE;
    if (this->_ravg_count < RAVG_BUFFER_SIZE) this->_ravg_count++;
    return this->_ravg_sum / this->_ravg_count;
}