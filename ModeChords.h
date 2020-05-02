#pragma once

#include "Mode.h"
#include "Gui.h"
#include "State.h"
#include "BtnHandlerMode.h"
#include "FaHandler.h"

class ModeChords : public Mode
{
private:
    BtnHandlerMode &_switchMode;
    FaHandler &_fa;

public:
    ModeChords(Controls &controls, Gui &gui, State &state, BtnHandlerMode &switchMode, FaHandler &fa);
};