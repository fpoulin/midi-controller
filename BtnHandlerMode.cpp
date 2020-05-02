#include "BtnHandlerMode.h"

BtnHandlerMode::BtnHandlerMode(Gui &gui): _gui(gui) {}

void BtnHandlerMode::onClick()
{
    _mode++;
    _mode = _mode% 8;
    _gui.switchMode(_mode);
}