#pragma once

#include "Mode.h"
#include "Gui.h"
#include "State.h"
#include "BtnHandlerMode.h"
#include "FaHandler.h"
#include "PotHandlerCursorX.h"
#include "PotHandlerCursorY.h"
#include "PotHandlerTranspose.h"

class ModePerform : public Mode
{
private:

    BtnHandlerMode &_switchMode;
    FaHandler &_fa;

    PotHandlerCursorX _cursorX;
    PotHandlerCursorY _cursorY;
    PotHandlerTranspose _transpose1;
    PotHandlerTranspose _transpose2;

public:
    ModePerform(Controls &controls, Gui &gui, State &state, BtnHandlerMode &switchMode, FaHandler &fa);
};