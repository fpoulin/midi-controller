#include "PotHandlerNudge.h"

PotHandlerNudge::PotHandlerNudge(Gui &gui, uint8_t maxAmount, bool horizontal): PotHandler(0, maxAmount), _gui(gui), _horizontal(horizontal) { }

void PotHandlerNudge::onChange(uint8_t oldValue, uint8_t newValue)
{
    _gui.nudge(newValue, _horizontal);
}