#include "State.h"

State::State()
{
    for (uint8_t i = 0; i < 4; i++)
    {
        this->_chords[i][0] = 48 + i * 12;
        this->_chords[i][1] = 51 + i * 12;
        this->_chords[i][2] = 53 + i * 12;
        this->_chords[i][3] = 55 + i * 12;
    }

    this->reset();
}

uint8_t State::getTrig(uint8_t step)
{
    return step % 16;
}

uint8_t State::getBeat(uint8_t step)
{
    return (step / 4) % 4;
}

uint8_t State::getBar(uint8_t step)
{
    return step / 16;
}

uint8_t State::hasTrigOn(uint8_t step, uint8_t channel)
{
    return this->_trigsOn[channel][this->getBar(step) % 2][this->getTrig(step)];
}

bool State::hasTrigOff(uint8_t step, uint8_t channel)
{
    return this->_trigsOff[channel][this->getBar(step) % 2][this->getTrig(step)];
}

bool State::isChordSelected(uint8_t step, uint8_t channel, uint8_t chordSelectionId)
{
    return this->_chordSel[0][this->getBar(step) % 8][this->getBeat(step)] == chordSelectionId;
}

bool State::isNoteSelected(uint8_t step, uint8_t channel, uint8_t noteSelectionId)
{
    uint8_t notesSel = this->_notesSel[channel][this->getBar(step) % 2][this->getTrig(step)];

    // bitmap -> first 4 bits are the notes selection within the chord
    return _notesToPlay[noteSelectionId] = ((128 >> noteSelectionId) & notesSel) != 0;
}

uint8_t *State::getNotes(uint8_t step, uint8_t channel)
{
    uint8_t choordSel = this->_chordSel[channel][this->getBar(step) % 8][this->getBeat(step)];

    for (uint8_t i = 0; i < 4; i++)
    {
        this->_notesToPlay[i] = this->isNoteSelected(step, channel, i)
            ? _chords[choordSel][i] + (this->_transpose[channel] - 2) * 12
            : 0;
    }

    return this->_notesToPlay;
}

void State::addChord(uint8_t *chord)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        this->_chords[_currChordInputId][i] = chord[i];
    }
    this->_currChordInputId = ++this->_currChordInputId % 4;
}

void State::setTrig(uint8_t step, uint8_t channel, bool state)
{
    // triggers on: [channel][bar%2][trig]
    this->_trigsOn[channel][this->getBar(step) % 2][this->getTrig(step)] = state ? 127 : 0;
}

void State::setChordSelected(uint8_t step, uint8_t chordSelectionId)
{
    // selection of a chord: [channel][bar%8][beat]
    this->_chordSel[0][this->getBar(step) % 8][this->getBeat(step)] = chordSelectionId;
    this->_chordSel[1][this->getBar(step) % 8][this->getBeat(step)] = chordSelectionId;
}

void State::setNoteSelected(uint8_t step, uint8_t channel, uint8_t noteSelectionId, bool state)
{
    // selection of notes: [channel][bar%2][trig]
    uint8_t mask = 128 >> noteSelectionId;
    if (state)
    {
        this->_notesSel[channel][this->getBar(step) % 2][this->getTrig(step)] |= mask;
    }
    else
    {
        this->_notesSel[channel][this->getBar(step) % 2][this->getTrig(step)] &= ~mask;
    }
}

void State::setTranspose(uint8_t channel, uint8_t octave)
{
    this->_transpose[channel] = octave;
}

void State::reset()
{
    randomSeed(millis());

    this->_currChordInputId = 0;

    // chords selections
    for (uint8_t i = 0; i < 8; i++)
    {
        for (uint8_t j = 0; j < 4; j++)
        {
            this->_chordSel[0][i][j] = i / 2;
            this->_chordSel[1][i][j] = i / 2;
        }
    }

    // notes selections and trigs
    for (uint8_t i = 0; i < 2; i++)
    {
        for (uint8_t j = 0; j < 16; j++)
        {
            // channel 1
            this->_notesSel[0][i][j] = 128 >> random(0, 4);
            this->_trigsOn[0][i][j] = random(0, 2) == 0 ? 127 : 0;
            this->_trigsOff[0][i][j] = false;

            // channel 2
            if (j == 0)
            {
                this->_notesSel[1][i][j] = 240; // full chord (11110000)
                this->_trigsOn[1][i][j] = 127;
                this->_trigsOff[1][i][j] = false;
            }
            else if (j < 8)
            {
                this->_notesSel[1][i][j] = 240; // full chord (11110000)
                this->_trigsOn[1][i][j] = 0;
                this->_trigsOff[1][i][j] = j == 3;
            }
            else if (j < 12)
            {
                this->_notesSel[1][i][j] = 128 >> (j - 8);
                this->_trigsOn[1][i][j] = 127;
                this->_trigsOff[1][i][j] = false;
            }
            else
            {
                this->_notesSel[1][i][j] = 128 >> (15 - j);
                this->_trigsOn[1][i][j] = true;
                this->_trigsOff[1][i][j] = false;
            }
        }
    }

    // transpose (setting octave nb, starting at -2)
    this->_transpose[0] = 2;
    this->_transpose[1] = 1;
}