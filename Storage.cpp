#include <arduino.h>
#include <EEPROM.h>
#include "Storage.h"

#define VERSION 1

Storage::Storage(State &state) : _state(state) {}

#define NB_CHORDS 4
#define NOTES_PER_CHORD 4

#define NB_CHANNELS 2

#define NB_CHORD_BARS 8
#define CHORDS_PER_BAR 4

#define NB_NOTES_BARS 2
#define NB_NOTES_PER_BAR 16

void Storage::writeState()
{
    int idx;

    EEPROM.update(idx++, VERSION);

    // chords
    for (uint8_t i = 0; i < NB_CHORDS; i++)
    {
        for (uint8_t j = 0; j < NOTES_PER_CHORD; j++)
        {
            EEPROM.update(idx++, this->_state._chords[i][j]);
        }
    }

    // chord selections
    for (uint8_t c = 0; c < NB_CHANNELS; c++)
    {
        for (uint8_t i = 0; i < NB_CHORD_BARS; i++)
        {
            for (uint8_t j = 0; j < CHORDS_PER_BAR; j++)
            {
                EEPROM.update(idx++, this->_state._chordSel[c][i][j]);
            }
        }
    }

    // note selections & trigs
    for (uint8_t c = 0; c < NB_CHANNELS; c++)
    {
        for (uint8_t i = 0; i < NB_NOTES_BARS; i++)
        {
            for (uint8_t j = 0; j < NB_NOTES_PER_BAR; j++)
            {
                EEPROM.update(idx++, this->_state._notesSel[c][i][j]);
                EEPROM.update(idx++, this->_state._trigs[c][i][j]);
            }
        }
    }

    // transpositions
    for (uint8_t c = 0; c < NB_CHANNELS; c++)
    {
        EEPROM.update(idx++, this->_state._transpose[c]);
    }
}

bool Storage::restoreState()
{
    int idx;

    uint8_t version = EEPROM.read(idx++);
    if (version != VERSION)
    {
        return false;
    }

    // chords
    for (uint8_t i = 0; i < NB_CHORDS; i++)
    {
        for (uint8_t j = 0; j < NOTES_PER_CHORD; j++)
        {
            this->_state._chords[i][j] = EEPROM.read(idx++);
        }
    }

    // chord selections
    for (uint8_t c = 0; c < NB_CHANNELS; c++)
    {
        for (uint8_t i = 0; i < NB_CHORD_BARS; i++)
        {
            for (uint8_t j = 0; j < CHORDS_PER_BAR; j++)
            {
                this->_state._chordSel[c][i][j] = EEPROM.read(idx++);
            }
        }
    }

    // note selections & trigs
    for (uint8_t c = 0; c < NB_CHANNELS; c++)
    {
        for (uint8_t i = 0; i < NB_NOTES_BARS; i++)
        {
            for (uint8_t j = 0; j < NB_NOTES_PER_BAR; j++)
            {
                this->_state._notesSel[c][i][j] = EEPROM.read(idx++);
                this->_state._trigs[c][i][j] = EEPROM.read(idx++);
            }
        }
    }

    // transpositions
    for (uint8_t c = 0; c < NB_CHANNELS; c++)
    {
        this->_state._transpose[c] = EEPROM.read(idx++);
    }

    return true;
}