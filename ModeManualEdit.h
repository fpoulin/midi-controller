#pragma once

#include "Mode.h"
#include "Gui.h"
#include "State.h"
#include "BtnHandlerMode.h"
#include "FaHandler.h"
#include "BtnhandlerClickCursor.h"
#include "BtnHandlerSaveEeprom.h"
#include "PotHandlerCursorX.h"
#include "PotHandlerCursorY.h"

class ModeManualEdit : public Mode
{
private:

    BtnHandlerMode &_switchMode;
    FaHandler &_fa;

    BtnHandlerClickCursor _clickCursor;
    BtnHandlerSaveEeprom _saveEeprom;
    PotHandlerCursorX _cursorX;
    PotHandlerCursorY _cursorY;

public:
    ModeManualEdit(Controls &controls, Gui &gui, State &state, Storage &storage, BtnHandlerMode &switchMode, FaHandler &fa);
};