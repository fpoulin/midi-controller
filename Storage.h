#include "State.h"

#pragma once

class Storage
{
private:
    State &_state;

public:
    Storage(State &state);
    void writeState();
    bool restoreState();
};