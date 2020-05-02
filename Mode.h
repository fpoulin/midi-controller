#pragma once

#include "Controls.h"

class Mode
{
private:
    Controls &_controls;
    BtnHandler &_btnHandler1;
    BtnHandler &_btnHandler2;
    BtnHandler &_btnHandler3;
    PotHandler &_potHandler1;
    PotHandler &_potHandler2;
    PotHandler &_potHandler3;
    PotHandler &_potHandler4;

public:
    Mode(Controls &controls, BtnHandler &btnhandler1, BtnHandler &btnhandler2, BtnHandler &btnhandler3, PotHandler &potHandler1, PotHandler &potHandler2, PotHandler &potHandler3, PotHandler &potHandler4);
    void Activate();
};