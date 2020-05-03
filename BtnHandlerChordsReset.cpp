#include "BtnHandlerChordsReset.h"

BtnHandlerChordsReset::BtnHandlerChordsReset(State &state) : _state(state) {}

void BtnHandlerChordsReset::onClick()
{
    _state.setHandleChordMode(1);
}