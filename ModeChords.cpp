#include "ModeChords.h"

ModeChords::ModeChords(Controls &controls, Gui &gui, State &state, BtnHandlerMode &switchMode, FaHandler &fa)
    : Mode(controls, switchMode, fa, fa, fa, fa, fa, fa)
    , _switchMode(switchMode)
    , _fa(fa) {}
