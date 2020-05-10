#include "BtnHandlerSaveEeprom.h"

BtnHandlerSaveEeprom::BtnHandlerSaveEeprom(Storage &storage, Gui &gui, bool stateOrSettings) : _storage(storage), _gui(gui), _stateOrSettings(stateOrSettings) {}

void BtnHandlerSaveEeprom::onClick()
{
    if (_stateOrSettings)
    {
        _storage.writeState();
        _gui.redraw(true);
    }
    else
    {
        _storage.writeSettings();
    }
}