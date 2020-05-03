#include "ModesManager.h"

#define NB_MODES 6

ModesManager::ModesManager(Gui &gui, State &state, Storage &storage, Controls &controls)
    : _gui(gui)
    , _state(state)
    , _controls(controls)
    , _fa(FaHandler())
    , _muteChannel1(BtnHandlerMuteChannel(state, 0))
    , _muteChannel2(BtnHandlerMuteChannel(state, 1))
    , _clickCursor(BtnHandlerClickCursor(gui))
    , _nudgeReset(BtnHandlerNudgeAction(gui, state, *this, false))
    , _nudgeApply(BtnHandlerNudgeAction(gui, state, *this, true))
    , _stepSequenceReset(BtnHandlerStepSequenceReset(state))
    , _loopSteps(BtnHandlerLoopSteps(gui))
    , _chordsReset(BtnHandlerChordsReset(state))
    , _saveEeprom(BtnHandlerSaveEeprom(storage, gui))
    , _cursorX(PotHandlerCursorX(gui))
    , _cursorY(PotHandlerCursorY(gui))
    , _transpose1(PotHandlerTranspose(0, state))
    , _transpose2(PotHandlerTranspose(1, state))
    , _nudgeH(PotHandlerNudge(gui, 31, true))
    , _nudgeV(PotHandlerNudge(gui, 3, false))
    {
        _controls.btn1.setCallback(*this);
        switchToMode(0);
    }

void ModesManager::onClick()
{
    _mode++;
    switchToMode(_mode % NB_MODES);
}

void ModesManager::switchToPerform()
{
    switchToMode(0);
}

void ModesManager::switchToMode(uint8_t mode)
{
    _mode = mode;
    _gui.switchMode(_mode);
    _state.resetAllNudges();

    switch (_mode)
    {
    case 0: // perform
        _gui.showCursor(false);
        _state.setHandleChordMode(0);
        _controls.btn2.setCallback(_muteChannel1);
        _controls.btn3.setCallback(_muteChannel2);
        _controls.pot1.setCallback(_fa);
        _controls.pot2.setCallback(_transpose1);
        _controls.pot3.setCallback(_fa);
        _controls.pot4.setCallback(_transpose2);
        break;

    case 1: // nudge
        _gui.showCursor(true);
        _state.setHandleChordMode(0);
        _controls.btn2.setCallback(_nudgeReset);
        _controls.btn3.setCallback(_nudgeApply);
        _controls.pot1.setCallback(_cursorY);
        _controls.pot2.setCallback(_fa);
        _controls.pot3.setCallback(_nudgeH);
        _controls.pot4.setCallback(_nudgeV);
        break;

    case 2: // step sequence
        _gui.showCursor(true);
        _state.setHandleChordMode(2);
        _controls.btn2.setCallback(_stepSequenceReset);
        _controls.btn3.setCallback(_loopSteps);
        _controls.pot1.setCallback(_cursorY);
        _controls.pot2.setCallback(_cursorX);
        _controls.pot3.setCallback(_fa);
        _controls.pot4.setCallback(_fa);
        break;

    case 3: // manual edit
        _gui.showCursor(true);
        _state.setHandleChordMode(0);
        _controls.btn2.setCallback(_clickCursor);
        _controls.btn3.setCallback(_saveEeprom);
        _controls.pot1.setCallback(_cursorY);
        _controls.pot2.setCallback(_cursorX);
        _controls.pot3.setCallback(_fa);
        _controls.pot4.setCallback(_fa);
        break;

    case 4: // chords
        _gui.showCursor(false);
        _state.setHandleChordMode(1);
        _controls.btn2.setCallback(_chordsReset);
        _controls.btn3.setCallback(_fa);
        _controls.pot1.setCallback(_fa);
        _controls.pot2.setCallback(_transpose1);
        _controls.pot3.setCallback(_fa);
        _controls.pot4.setCallback(_transpose2);
        break;

    case 5: // settings
        _gui.showCursor(false);
        _state.setHandleChordMode(0);
        _controls.btn2.setCallback(_fa);
        _controls.btn3.setCallback(_fa);
        _controls.pot1.setCallback(_fa);
        _controls.pot2.setCallback(_fa);
        _controls.pot3.setCallback(_fa);
        _controls.pot4.setCallback(_fa);
        break;
    }
}