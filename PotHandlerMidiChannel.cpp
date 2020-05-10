#include "PotHandlerMidiChannel.h"
#include "MidiIo.h"

PotHandlerMidiChannel::PotHandlerMidiChannel(Gui &gui, uint8_t channelIdx) : PotHandler(1, 16), _gui(gui), _channelIdx(channelIdx) {}

void PotHandlerMidiChannel::onChange(uint8_t oldValue, uint8_t newValue)
{
    _gui.showNumber(newValue);
    
    if (_channelIdx < 16)
    {
        midiIo::setMidiChannelOut(_channelIdx, newValue);
    }
    else
    {
        midiIo::setMidiChannelIn(newValue);
    }
}