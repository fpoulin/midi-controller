#include "ModeManualEdit.h"

ModeManualEdit::ModeManualEdit(Controls &controls, Gui &gui, State &state, Storage &storage, BtnHandlerMode &switchMode, FaHandler &fa)
    : Mode(controls, switchMode, _clickCursor, _saveEeprom, _cursorY, _cursorX, fa, fa)
    , _switchMode(switchMode)
    , _fa(fa)
    , _clickCursor(BtnHandlerClickCursor(gui))
    , _saveEeprom(BtnHandlerSaveEeprom(storage, gui))
    , _cursorX(PotHandlerCursorX(gui))
    , _cursorY(PotHandlerCursorY(gui)) {}
