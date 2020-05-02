#include "PotHandlerCursorX.h"

PotHandlerCursorX::PotHandlerCursorX(Gui &gui): PotHandler(0, 31), _gui(gui) { }

void PotHandlerCursorX::onChange(uint8_t oldValue, uint8_t newValue)
{
    _gui.moveCursorX(newValue);
}