#include "BtnHandlerLoopSteps.h"

BtnHandlerLoopSteps::BtnHandlerLoopSteps(Gui &gui) : _gui(gui) {}

void BtnHandlerLoopSteps::onClick()
{
    _gui.loopSteps();
}