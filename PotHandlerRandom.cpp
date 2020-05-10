#include "PotHandlerRandom.h"

PotHandlerRandom::PotHandlerRandom(uint8_t channel, State &state): PotHandler(0, 10), _channel(channel), _state(state) { }

void PotHandlerRandom::onChange(uint8_t oldValue, uint8_t newValue)
{
    _state.setSwag(_channel, newValue);
}