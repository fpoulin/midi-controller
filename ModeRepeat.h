#pragma once

#include "Mode.h"
#include "Gui.h"
#include "State.h"
#include "BtnHandlerMode.h"
#include "FaHandler.h"
#include "PotHandlerCursorX.h"
#include "PotHandlerCursorY.h"

class ModeRepeat : public Mode
{
private:
    BtnHandlerMode &_switchMode;
    FaHandler &_fa;

    PotHandlerCursorX _cursorX;
    PotHandlerCursorY _cursorY;

public:
    ModeRepeat(Controls &controls, Gui &gui, State &state, BtnHandlerMode &switchMode, FaHandler &fa);
};