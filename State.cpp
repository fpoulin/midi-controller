#include "State.h"
#include <arduino.h>

int _step = 0;

unsigned char notes[4];
unsigned char shift = 0;

State::State() {
    notes[0] = 36;
    notes[1] = 39;
    notes[2] = 41;
    notes[3] = 43;
}

void State::setStep(int step) {
    _step = step;
    if(step % 32 == 0) {
        shift = rand() % 10;
    }
}

int State::getStep() {
    return _step;
}

unsigned char State::getNote() {
    return notes[_step % 4] + shift;
}