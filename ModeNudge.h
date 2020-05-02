#pragma once

#include "Mode.h"
#include "Gui.h"
#include "State.h"
#include "BtnHandlerMode.h"
#include "FaHandler.h"
#include "PotHandlerCursorY.h"

class ModeNudge : public Mode
{
private:

    BtnHandlerMode &_switchMode;
    FaHandler &_fa;

    PotHandlerCursorY _cursorY;

public:
    ModeNudge(Controls &controls, Gui &gui, State &state, BtnHandlerMode &switchMode, FaHandler &fa);
};