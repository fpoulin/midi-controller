#pragma once

#include "BtnHandler.h"

class BtnHandlerSaveEeprom : public BtnHandler
{
public:
    BtnHandlerSaveEeprom();
    virtual void onClick();
};