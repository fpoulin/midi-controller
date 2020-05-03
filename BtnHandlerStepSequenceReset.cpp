#include "BtnHandlerStepSequenceReset.h"

BtnHandlerStepSequenceReset::BtnHandlerStepSequenceReset(State &state) : _state(state) {}

void BtnHandlerStepSequenceReset::onClick()
{
    _state.setHandleChordMode(2);
}