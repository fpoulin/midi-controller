#pragma once

#include "PotHandler.h"
#include "BtnHandler.h"

class FaHandler : public BtnHandler, public PotHandler
{
public:
    FaHandler();
    void onClick() override;
    void onChange(uint8_t oldValue, uint8_t newValue) override;
};