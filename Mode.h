#pragma once

#include "Controls.h"

class Mode
{
private:
    Controls &_controls;

protected:
    virtual PotHandler &getPotHandler1() = 0;
    virtual PotHandler &getPotHandler2() = 0;
    virtual PotHandler &getPotHandler3() = 0;
    virtual PotHandler &getPotHandler4() = 0;

public:
    Mode(Controls &controls);
    void Activate();
};