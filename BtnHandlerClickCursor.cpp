#include "BtnHandlerClickCursor.h"

BtnHandlerClickCursor::BtnHandlerClickCursor(Gui &gui) : _gui(gui) {}

void BtnHandlerClickCursor::onClick()
{
    _gui.clickCursor();
}