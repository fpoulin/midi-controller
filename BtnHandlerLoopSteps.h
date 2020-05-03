#pragma once

#include "BtnHandler.h"
#include "Gui.h"

class BtnHandlerLoopSteps : public BtnHandler
{
private:
    Gui &_gui;

public:
    BtnHandlerLoopSteps(Gui &gui);
    void onClick() override;
};