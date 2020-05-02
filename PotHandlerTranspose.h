#pragma once

#include "PotHandler.h"
#include "State.h"

class PotHandlerTranspose : public PotHandler
{
private:
    State &_state;
    uint8_t _channel;

public:
    PotHandlerTranspose(uint8_t channel, State &state);
    virtual void onChange(uint8_t oldValue, uint8_t newValue);
};