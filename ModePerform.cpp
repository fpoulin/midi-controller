#include "ModePerform.h"

ModePerform::ModePerform(Controls &controls, Gui &gui, State &state)
    : Mode(controls), _cursorY(gui), _cursorX(gui), _transpose1(0, state), _transpose2(1, state) {}

PotHandler &ModePerform::getPotHandler1()
{
    return _cursorY;
}

PotHandler &ModePerform::getPotHandler2()
{
    return _cursorX;
}

PotHandler &ModePerform::getPotHandler3()
{
    return _transpose1;
}

PotHandler &ModePerform::getPotHandler4()
{
    return _transpose2;
}
