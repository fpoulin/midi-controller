#pragma once

#include "Mode.h"
#include "Gui.h"
#include "State.h"
#include "PotHandlerCursorX.h"
#include "PotHandlerCursorY.h"
#include "PotHandlerTranspose.h"

class ModePerform : public Mode
{
private:
    PotHandlerCursorX _cursorX;
    PotHandlerCursorY _cursorY;
    PotHandlerTranspose _transpose1;
    PotHandlerTranspose _transpose2;

protected:
    PotHandler &getPotHandler1();
    PotHandler &getPotHandler2();
    PotHandler &getPotHandler3();
    PotHandler &getPotHandler4();

public:
    ModePerform(Controls &controls, Gui &gui, State &state);
};