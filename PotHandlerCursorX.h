#pragma once

#include "PotHandler.h"
#include "Gui.h"

class PotHandlerCursorX : public PotHandler
{
private:
    Gui &_gui;

public:
    PotHandlerCursorX(Gui &gui);
    virtual void onChange(uint8_t oldValue, uint8_t newValue);
};