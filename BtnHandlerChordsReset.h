#pragma once

#include "BtnHandler.h"
#include "State.h"

class BtnHandlerChordsReset : public BtnHandler
{
private:
    State &_state;

public:
    BtnHandlerChordsReset(State &state);
    void onClick() override;
};