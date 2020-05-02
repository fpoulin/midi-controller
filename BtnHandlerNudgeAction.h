#pragma once

#include "BtnHandler.h"
#include "Gui.h"
#include "State.h"

class ModesManager; // forward declaration (circular dependency)

class BtnHandlerNudgeAction : public BtnHandler
{
private:
    Gui &_gui; 
    State &_state;
    ModesManager &_modesManager;
    bool _apply;

public:
    BtnHandlerNudgeAction(Gui &gui, State &state, ModesManager &modesManager, bool apply);
    void onClick() override;
};