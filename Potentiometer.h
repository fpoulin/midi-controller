#pragma once

#define RAVG_BUFFER_SIZE 8

#include <Arduino.h>

class Potentiometer
{
private:
    uint8_t _pin;
    uint8_t _value = 0;
    uint8_t _min = 0;
    uint8_t _max = 255;
    void (*_onChange)(uint8_t oldValue, uint8_t newValue) = NULL;

    int _ravg_buffer[RAVG_BUFFER_SIZE] = {0};
    uint8_t _ravg_idx = 0;
    unsigned int _ravg_sum = 0;
    uint8_t _ravg_count = 0;
    int ravg(int x);
public:
    Potentiometer(uint8_t pin);
    void peek();
    void setCallback(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max);
};