#pragma once

#include "BtnHandler.h"
#include "Gui.h"

class BtnHandlerMode : public BtnHandler
{
private:
    Gui &_gui;
    uint8_t _mode;

public:
    BtnHandlerMode(Gui &gui);
    void onClick() override;
};