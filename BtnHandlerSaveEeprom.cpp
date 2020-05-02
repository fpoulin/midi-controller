#include "BtnHandlerSaveEeprom.h"

BtnHandlerSaveEeprom::BtnHandlerSaveEeprom(Storage &storage, Gui &gui): _storage(storage), _gui(gui) {}

void BtnHandlerSaveEeprom::onClick()
{
    _storage.writeState();
    _gui.redraw(true);
}