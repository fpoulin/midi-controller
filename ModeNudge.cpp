#include "ModeNudge.h"

ModeNudge::ModeNudge(Controls &controls, Gui &gui, State &state, BtnHandlerMode &switchMode, FaHandler &fa)
    : Mode(controls, switchMode, fa, fa, _cursorY, fa, fa, fa)
    , _switchMode(switchMode)
    , _fa(fa)
    , _cursorY(PotHandlerCursorY(gui)) {}
