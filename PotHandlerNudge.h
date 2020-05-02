#pragma once

#include "PotHandler.h"
#include "Gui.h"

class PotHandlerNudge : public PotHandler
{
private:
    Gui &_gui;
    bool _horizontal;

public:
    PotHandlerNudge(Gui &gui, uint8_t maxAmount, bool horizontal);
    void onChange(uint8_t oldValue, uint8_t newValue) override;
};