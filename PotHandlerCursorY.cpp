#include "PotHandlerCursorY.h"

PotHandlerCursorY::PotHandlerCursorY(Gui &gui): PotHandler(0, 15), _gui(gui) { }

void PotHandlerCursorY::onChange(uint8_t oldValue, uint8_t newValue)
{
    _gui.moveCursorY(newValue);
}