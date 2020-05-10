#pragma once

#include "BtnHandler.h"
#include "Gui.h"
#include "Controls.h"

#include "FaHandler.h"
#include "BtnHandlerMuteChannel.h"
#include "BtnHandlerClickCursor.h"
#include "BtnHandlerNudgeAction.h"
#include "BtnHandlerStepSequenceReset.h"
#include "BtnHandlerLoopSteps.h"
#include "BtnHandlerChordsReset.h"
#include "BtnHandlerSaveEeprom.h"
#include "PotHandlerCursorX.h"
#include "PotHandlerCursorY.h"
#include "PotHandlerTranspose.h"
#include "PotHandlerNudge.h"
#include "PotHandlerRandom.h"
#include "PotHandlerMidiChannel.h"

class ModesManager : public BtnHandler
{
private:
    Gui &_gui;
    State &_state;
    Controls &_controls;

    FaHandler _fa;
    BtnHandlerMuteChannel _muteChannel1;
    BtnHandlerMuteChannel _muteChannel2;
    BtnHandlerClickCursor _clickCursor;
    BtnHandlerNudgeAction _nudgeReset;
    BtnHandlerNudgeAction _nudgeApply;
    BtnHandlerStepSequenceReset _stepSequenceReset;
    BtnHandlerLoopSteps _loopSteps;
    BtnHandlerChordsReset _chordsReset;
    BtnHandlerSaveEeprom _saveStateEeprom;
    BtnHandlerSaveEeprom _saveSettingsEeprom;
    PotHandlerCursorX _cursorX;
    PotHandlerCursorY _cursorY;
    PotHandlerRandom _rand1;
    PotHandlerRandom _rand2;
    PotHandlerTranspose _transpose1;
    PotHandlerTranspose _transpose2;
    PotHandlerNudge _nudgeH;
    PotHandlerNudge _nudgeV;
    PotHandlerMidiChannel _channelIn;
    PotHandlerMidiChannel _channelOut1;
    PotHandlerMidiChannel _channelOut2;

    uint8_t _mode;

    void switchToMode(uint8_t mode);

public:
    ModesManager(Gui &gui, State &state, Storage &storage, Controls &controls);
    void onClick() override;
    void switchToPerform();
};