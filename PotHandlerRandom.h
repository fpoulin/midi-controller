#pragma once

#include "PotHandler.h"
#include "State.h"

class PotHandlerRandom : public PotHandler
{
private:
    State &_state;
    uint8_t _channel;

public:
    PotHandlerRandom(uint8_t channel, State &state);
    void onChange(uint8_t oldValue, uint8_t newValue) override;
};