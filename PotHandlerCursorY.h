#pragma once

#include "PotHandler.h"
#include "Gui.h"

class PotHandlerCursorY : public PotHandler
{
private:
    Gui &_gui;

public:
    PotHandlerCursorY(Gui &gui);
    virtual void onChange(uint8_t oldValue, uint8_t newValue);
};