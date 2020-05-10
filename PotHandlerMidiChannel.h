#pragma once

#include "PotHandler.h"
#include "Gui.h"

class PotHandlerMidiChannel : public PotHandler
{
private:
    Gui &_gui;
    uint8_t _channelIdx; // 15+ -> to midi IN

public:
    PotHandlerMidiChannel(Gui &gui, uint8_t channelIdx);
    void onChange(uint8_t oldValue, uint8_t newValue) override;
};