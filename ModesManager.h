#pragma once

#include "BtnHandler.h"
#include "Gui.h"
#include "Controls.h"

#include "FaHandler.h"
#include "BtnHandlerClickCursor.h"
#include "BtnHandlerSaveEeprom.h"
#include "PotHandlerCursorX.h"
#include "PotHandlerCursorY.h"
#include "PotHandlerTranspose.h"

class ModesManager : public BtnHandler
{
private:
    Gui &_gui;
    Controls &_controls;

    FaHandler _fa;
    BtnHandlerClickCursor _clickCursor;
    BtnHandlerSaveEeprom _saveEeprom;
    PotHandlerCursorX _cursorX;
    PotHandlerCursorY _cursorY;
    PotHandlerTranspose _transpose1;
    PotHandlerTranspose _transpose2;

    uint8_t _mode;

public:
    ModesManager(Gui &gui, State &state, Storage &storage, Controls &controls);
    void onClick() override;
};