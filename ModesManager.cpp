#include "ModesManager.h"

#define NB_MODES 8

ModesManager::ModesManager(Gui &gui, State &state, Storage &storage, Controls &controls)
    : _gui(gui)
    , _controls(controls)
    , _fa(FaHandler())
    , _clickCursor(BtnHandlerClickCursor(gui))
    , _saveEeprom(BtnHandlerSaveEeprom(storage, gui))
    , _cursorX(PotHandlerCursorX(gui))
    , _cursorY(PotHandlerCursorY(gui))
    , _transpose1(PotHandlerTranspose(0, state))
    , _transpose2(PotHandlerTranspose(1, state))
    {
        _controls.btn1.setCallback(*this);
        _mode = NB_MODES - 1;
        onClick();
    }

void ModesManager::onClick()
{
    _mode++;
    _mode = _mode % NB_MODES;
    _gui.switchMode(_mode);

    switch (_mode)
    {
    case 0: // perform
        _controls.btn2.setCallback(_fa);
        _controls.btn3.setCallback(_fa);
        _controls.pot1.setCallback(_fa);
        _controls.pot2.setCallback(_transpose1);
        _controls.pot3.setCallback(_fa);
        _controls.pot4.setCallback(_transpose2);
        break;

    case 1: // nudge
        _controls.btn2.setCallback(_fa);
        _controls.btn3.setCallback(_fa);
        _controls.pot1.setCallback(_cursorY);
        _controls.pot2.setCallback(_fa);
        _controls.pot3.setCallback(_fa);
        _controls.pot4.setCallback(_fa);
        break;

    case 2: // randomize
        _controls.btn2.setCallback(_fa);
        _controls.btn3.setCallback(_fa);
        _controls.pot1.setCallback(_cursorY);
        _controls.pot2.setCallback(_fa);
        _controls.pot3.setCallback(_fa);
        _controls.pot4.setCallback(_fa);
        break;

    case 3: // repeat
        _controls.btn2.setCallback(_fa);
        _controls.btn3.setCallback(_fa);
        _controls.pot1.setCallback(_cursorY);
        _controls.pot2.setCallback(_cursorX);
        _controls.pot3.setCallback(_fa);
        _controls.pot4.setCallback(_fa);
        break;

    case 4: // manual edit
        _controls.btn2.setCallback(_clickCursor);
        _controls.btn3.setCallback(_saveEeprom);
        _controls.pot1.setCallback(_cursorY);
        _controls.pot2.setCallback(_cursorX);
        _controls.pot3.setCallback(_fa);
        _controls.pot4.setCallback(_fa);
        break;

    case 5: // step sequence
        _controls.btn2.setCallback(_fa);
        _controls.btn3.setCallback(_fa);
        _controls.pot1.setCallback(_cursorY);
        _controls.pot2.setCallback(_fa);
        _controls.pot3.setCallback(_fa);
        _controls.pot4.setCallback(_fa);
        break;

    case 6: // chords
        _controls.btn2.setCallback(_fa);
        _controls.btn3.setCallback(_fa);
        _controls.pot1.setCallback(_fa);
        _controls.pot2.setCallback(_fa);
        _controls.pot3.setCallback(_fa);
        _controls.pot4.setCallback(_fa);
        break;

    case 7: // settings
        _controls.btn2.setCallback(_fa);
        _controls.btn3.setCallback(_fa);
        _controls.pot1.setCallback(_fa);
        _controls.pot2.setCallback(_fa);
        _controls.pot3.setCallback(_fa);
        _controls.pot4.setCallback(_fa);
        break;
    }
}