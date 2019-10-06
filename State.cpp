#include "State.h"

int _state = 0;

void State::setState(int state) {
    _state = state;
}

int State::getState() {
    return _state;
}