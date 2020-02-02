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

void State::addChord(uint8_t *chord)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        this->_chords[_currChordInputId][i] = chord[i];
    }
    this->_currChordInputId = ++this->_currChordInputId % 4;
}

void State::moveToStep(uint8_t step)
{
    this->_currStep = step;
    this->_currBar = step / 16;

    this->_currBeat = (step / 4) % 4;
    this->_currTrig = step % 16;
}

uint8_t State::hasTrigOn(uint8_t channel)
{
    return this->_trigsOn[channel][this->_currBar % 2][this->_currTrig];
}

bool State::hasTrigOff(uint8_t channel)
{
    return this->_trigsOff[channel][this->_currBar % 2][this->_currTrig];
}

bool State::isChordSelected(uint8_t channel, uint8_t chordSelectionId)
{
    return this->_chordSel[0][this->_currBar % 8][this->_currBeat] == chordSelectionId;
}

bool State::isNoteSelected(uint8_t channel, uint8_t noteSelectionId)
{
    uint8_t notesSel = this->_notesSel[channel][this->_currBar % 2][this->_currTrig];

    // bitmap -> first 4 bits are the notes selection within the chord
    return _notesToPlay[noteSelectionId] = ((128 >> noteSelectionId) & notesSel) != 0;
}

uint8_t *State::getNotes(uint8_t channel)
{
    uint8_t choordSel = this->_chordSel[channel][this->_currBar % 8][this->_currBeat];

    for (uint8_t i = 0; i < 4; i++)
    {
        this->_notesToPlay[i] = this->isNoteSelected(channel, i)
                                    ? _chords[choordSel][i] + this->_transpose[channel]
                                    : 0;
    }

    return this->_notesToPlay;
}

void State::reset()
{
    randomSeed(millis());
    
    this->_currChordInputId = 0;

    this->_currStep = 0;
    this->_currBar = 0;
    this->_currBeat = 0;
    this->_currTrig = 0;

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
            this->_notesSel[0][i][j] = 128 >> random(0,4);
            this->_trigsOn[0][i][j] = random(0,2) == 0;
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

    // transpose
    this->_transpose[0] = 0;
    this->_transpose[1] = 0;
}