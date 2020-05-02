#pragma once

#include <Arduino.h>

class PotHandler
{
public:
    PotHandler(uint8_t min, uint8_t max);
    uint8_t minValue;
    uint8_t maxValue;
    virtual void onChange(uint8_t oldValue, uint8_t newValue) = 0;
    virtual ~PotHandler() = 0;
};

inline PotHandler::~PotHandler() {}