#include "State.h"
#include <arduino.h>

State::State()
{
    this->_currNote = 0;
    this->_currChord = 0;
    this->_currChordInputId = 0;

    this->_trigs[0] = 170; // 10101010
    this->_trigs[1] = 170;
    this->_trigs[2] = 170;
    this->_trigs[3] = 170;

    for (int i = 0; i < 4; i++)
    {
        this->_chords[i][0] = 36 + i * 12;
        this->_chords[i][1] = 39 + i * 12;
        this->_chords[i][2] = 41 + i * 12;
        this->_chords[i][3] = 43 + i * 12;
    }
}

void State::addChord(unsigned char *chord)
{
    this-> _currChordInputId = this-> _currChordInputId++ % 4;
    for (int i = 0; i < 4; i++)
    {
        this->_chords[_currChordInputId][i] = chord[i];
    }
}

void State::moveToStep(int step)
{
    this->_currTrig = 128 >> step % 8;
    this->_currBeat = (step / 4) % 4;
    this->_currChord = (step / 32) % 4; // switch chord every 2 bars
}

bool State::hasNote()
{
    return this->_trigs[this->_currBeat] & this->_currTrig;
}

unsigned char State::getNote()
{
    return this->_chords[this->_currChord][this->_currNote++ % 4];
}

void State::reset()
{
    this->_currTrig = 0;
    this->_currNote = 0;
    this->_currBeat = 0;
    this->_currChord = 0;
    this->_currChordInputId = 0;
}