#pragma once

#include "BtnHandler.h"
#include "Storage.h"
#include "Gui.h"

class BtnHandlerSaveEeprom : public BtnHandler
{
private:
    Storage &_storage;
    Gui &_gui;
    bool _stateOrSettings;

public:
    BtnHandlerSaveEeprom(Storage &storage, Gui &gui, bool stateOrSettings);
    void onClick() override;
};