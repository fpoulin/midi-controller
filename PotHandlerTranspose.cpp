#include "PotHandlerTranspose.h"

PotHandlerTranspose::PotHandlerTranspose(uint8_t channel, State &state): PotHandler(0, 4), _channel(channel), _state(state) { }

void PotHandlerTranspose::onChange(uint8_t oldValue, uint8_t newValue)
{
    _state.setTranspose(_channel, newValue);
}