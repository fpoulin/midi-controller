#pragma once

#include "Mode.h"
#include "Gui.h"
#include "State.h"
#include "BtnHandlerMode.h"
#include "FaHandler.h"
#include "BtnHandlerSaveEeprom.h"

class ModeSettings : public Mode
{
private:

    BtnHandlerMode &_switchMode;
    FaHandler &_fa;

public:
    ModeSettings(Controls &controls, Gui &gui, State &state, Storage &storage, BtnHandlerMode &switchMode, FaHandler &fa);
};