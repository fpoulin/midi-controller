#include "ModeSettings.h"

ModeSettings::ModeSettings(Controls &controls, Gui &gui, State &state, Storage &storage, BtnHandlerMode &switchMode, FaHandler &fa)
    : Mode(controls, switchMode, fa, fa, fa, fa, fa, fa)
    , _switchMode(switchMode)
    , _fa(fa) {}
