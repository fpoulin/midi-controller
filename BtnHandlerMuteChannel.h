#pragma once

#include "BtnHandler.h"
#include "State.h"

class BtnHandlerMuteChannel : public BtnHandler
{
private:
    State &_state;
    uint8_t _channel;

public:
    BtnHandlerMuteChannel(State &state, uint8_t channel);
    void onClick() override;
};