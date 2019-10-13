#include "State.h"
#include <arduino.h>

BEGIN_STATE_NAMESPACE

State::State() {

    _currNote = 0;

    trigs[0] = 138;
    trigs[1] = 40;
    trigs[2] = 162;
    trigs[3] = 138;
    trigs[4] = 138;
    trigs[5] = 40;
    trigs[6] = 162;
    trigs[7] = 138;

    notes[0] = 36 + 12;
    notes[1] = 39 + 12;
    notes[2] = 41 + 12;
    notes[3] = 43 + 12;
}

void State::setStep(int step) {
    _currBeat = (step / 8) % 8;
    _currTrig = 128 >> step % 8 ;
    _currNote = _currBeat == 0 && _currTrig == 0 ? 0 : _currNote;
}

bool State::hasNote() {
    return trigs[_currBeat] & _currTrig;
}

unsigned char State::getNote() {
    return notes[_currNote++ % 4];
}

END_STATE_NAMESPACE