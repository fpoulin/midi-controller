#pragma once

#include "PotHandler.h"
#include "BtnHandler.h"

class FaHandler : public BtnHandler, public PotHandler
{
public:
    FaHandler();
    virtual void onClick();
    virtual void onChange(uint8_t oldValue, uint8_t newValue);
};