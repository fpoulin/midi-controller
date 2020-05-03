#include "BtnHandlerMuteChannel.h"

BtnHandlerMuteChannel::BtnHandlerMuteChannel(State &state, uint8_t channel) : _state(state), _channel(channel) {}

void BtnHandlerMuteChannel::onClick()
{
    _state.toggleMuteChannel(_channel);
}