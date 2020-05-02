#include "Mode.h"
#include "BtnHandler.h"
#include "PotHandler.h"

Mode::Mode(Controls &controls, BtnHandler &btnHandler1, BtnHandler &btnHandler2, BtnHandler &btnHandler3, PotHandler &potHandler1, PotHandler &potHandler2, PotHandler &potHandler3, PotHandler &potHandler4)
    : _controls(controls), _btnHandler1(btnHandler1), _btnHandler2(btnHandler2), _btnHandler3(btnHandler3), _potHandler1(potHandler1), _potHandler2(potHandler2), _potHandler3(potHandler3), _potHandler4(potHandler4) {}

void Mode::Activate()
{
    _controls.btn1.setCallback(_btnHandler1);
    _controls.btn2.setCallback(_btnHandler2);
    _controls.btn3.setCallback(_btnHandler3);
    
    _controls.pot1.setCallback(_potHandler1);
    _controls.pot2.setCallback(_potHandler2);
    _controls.pot3.setCallback(_potHandler3);
    _controls.pot4.setCallback(_potHandler4);
}