#include "BtnHandlerNudgeAction.h"
#include "ModesManager.h"

BtnHandlerNudgeAction::BtnHandlerNudgeAction(Gui &gui, State &state, ModesManager &modesManager, bool apply)
    : _gui(gui)
    , _state(state)
    , _modesManager(modesManager)
    , _apply(apply) {}

void BtnHandlerNudgeAction::onClick()
{
    if (_apply)
    {
        _state.applyAllNudges();
    }
    else
    {
        _state.resetAllNudges();
    }

    _gui.redraw(false);
    _modesManager.switchToPerform();
}