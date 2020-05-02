#include "ModePerform.h"

ModePerform::ModePerform(Controls &controls, Gui &gui, State &state, BtnHandlerMode &switchMode, FaHandler &fa)
    : Mode(controls, switchMode, fa, fa, _cursorY, _cursorX, _transpose1, _transpose2)
    , _switchMode(switchMode)
    , _fa(fa)
    , _cursorX(PotHandlerCursorX(gui))
    , _cursorY(PotHandlerCursorY(gui))
    , _transpose1(PotHandlerTranspose(0, state))
    , _transpose2(PotHandlerTranspose(1, state)) {}
