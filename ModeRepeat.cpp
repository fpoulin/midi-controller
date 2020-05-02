#include "ModeRepeat.h"

ModeRepeat::ModeRepeat(Controls &controls, Gui &gui, State &state, BtnHandlerMode &switchMode, FaHandler &fa)
    : Mode(controls, switchMode, fa, fa, _cursorY, _cursorX, fa, fa)
    , _switchMode(switchMode)
    , _fa(fa)
    , _cursorX(PotHandlerCursorX(gui))
    , _cursorY(PotHandlerCursorY(gui)) {}
