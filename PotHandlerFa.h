#pragma once

#include "PotHandler.h"

class PotHandlerFa : public PotHandler
{
public:
    PotHandlerFa();
    virtual void onChange(uint8_t oldValue, uint8_t newValue);
};