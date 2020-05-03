#pragma once

#include "BtnHandler.h"
#include "State.h"

class BtnHandlerStepSequenceReset : public BtnHandler
{
private:
    State &_state;

public:
    BtnHandlerStepSequenceReset(State &state);
    void onClick() override;
};