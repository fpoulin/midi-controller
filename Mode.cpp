#include "Mode.h"
#include "PotHandler.h"

Mode::Mode(Controls &controls) : _controls(controls) {}

void Mode::Activate()
{
    _controls.pot1.setCallback(getPotHandler1());
    _controls.pot2.setCallback(getPotHandler2());
    _controls.pot3.setCallback(getPotHandler3());
    _controls.pot4.setCallback(getPotHandler4());
}