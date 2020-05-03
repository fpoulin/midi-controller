#pragma once

#include "BtnHandler.h"
#include "Gui.h"
#include "Controls.h"

#include "FaHandler.h"
#include "BtnHandlerClickCursor.h"
#include "BtnHandlerNudgeAction.h"
#include "BtnHandlerSaveEeprom.h"
#include "PotHandlerCursorX.h"
#include "PotHandlerCursorY.h"
#include "PotHandlerTranspose.h"
#include "PotHandlerNudge.h"

class ModesManager : public BtnHandler
{
private:
    Gui &_gui;
    State &_state;
    Controls &_controls;

    FaHandler _fa;
    BtnHandlerClickCursor _clickCursor;
    BtnHandlerNudgeAction _nudgeReset;
    BtnHandlerNudgeAction _nudgeApply;
    BtnHandlerSaveEeprom _saveEeprom;
    PotHandlerCursorX _cursorX;
    PotHandlerCursorY _cursorY;
    PotHandlerTranspose _transpose1;
    PotHandlerTranspose _transpose2;
    PotHandlerNudge _nudgeH;
    PotHandlerNudge _nudgeV;

    uint8_t _mode;

    void switchToMode(uint8_t mode);

public:
    ModesManager(Gui &gui, State &state, Storage &storage, Controls &controls);
    void onClick() override;
    void switchToPerform();
};