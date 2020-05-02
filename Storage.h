#pragma once

#include "State.h"

class Storage
{
private:
    State &_state;

public:
    Storage(State &state);
    void writeState(); // use with caution
    bool restoreState();
};