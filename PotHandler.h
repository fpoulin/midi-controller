#pragma once

#include <Arduino.h>

class PotHandler
{
public:
    PotHandler(uint8_t min, uint8_t max);
    virtual void onChange(uint8_t oldValue, uint8_t newValue) = 0;
    uint8_t getMin();
    uint8_t getMax();
    virtual ~PotHandler() = 0;

protected:
    uint8_t _min;
    uint8_t _max;
};

inline PotHandler::~PotHandler() {}