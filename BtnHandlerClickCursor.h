#pragma once

#include "BtnHandler.h"
#include "Gui.h"

class BtnHandlerClickCursor : public BtnHandler
{
private:
    Gui &_gui;

public:
    BtnHandlerClickCursor(Gui &gui);
    void onClick() override;
};