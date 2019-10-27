#include "State.h"
#include <arduino.h>

State::State() {

    this->_currNote = 0;

    this->_trigs[0] = 138;
    this->_trigs[1] = 40;
    this->_trigs[2] = 162;
    this->_trigs[3] = 138;
    this->_trigs[4] = 138;
    this->_trigs[5] = 40;
    this->_trigs[6] = 162;
    this->_trigs[7] = 138;

    this->_notes[0] = 36 + 12;
    this->_notes[1] = 39 + 12;
    this->_notes[2] = 41 + 12;
    this->_notes[3] = 43 + 12;
}

void State::setStep(int step) {
    this->_currBeat = (step / 8) % 8;
    this->_currTrig = 128 >> step % 8 ;
    this->_currNote = this->_currBeat == 0 && this->_currTrig == 0 ? 0 : this->_currNote;
}

bool State::hasNote() {
    return this->_trigs[this->_currBeat] & this->_currTrig;
}

unsigned char State::getNote() {
    return this->_notes[this->_currNote++ % 4];
}