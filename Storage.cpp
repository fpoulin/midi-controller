#include <arduino.h>
#include <EEPROM.h>
#include "Storage.h"

Storage::Storage(State &state) : _state(state) {}

void Storage::writeState()
{
    int idx;

    EEPROM.update(idx++, STORAGE_VERSION);

    // chords
    for (uint8_t i = 0; i < NB_CHORDS; i++)
    {
        for (uint8_t j = 0; j < NB_NOTES_PER_CHORD; j++)
        {
            EEPROM.update(idx++, _state._chords[i][j]);
        }
    }

    // chord selections
    for (uint8_t c = 0; c < NB_CHANNELS; c++)
    {
        for (uint8_t i = 0; i < NB_CHORD_BARS; i++)
        {
            for (uint8_t j = 0; j < NB_CHORDS_PER_BAR; j++)
            {
                EEPROM.update(idx++, _state._chordSel[c][i][j]);
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
                EEPROM.update(idx++, _state._notesSel[c][i][j]);
                EEPROM.update(idx++, _state._trigs[c][i][j]);
            }
        }
    }

    // transpositions
    for (uint8_t c = 0; c < NB_CHANNELS; c++)
    {
        EEPROM.update(idx++, _state._transpose[c]);
    }
}

bool Storage::restoreState()
{
    int idx;

    uint8_t version = EEPROM.read(idx++);
    if (version != STORAGE_VERSION)
    {
        _state.reset(false);
        return false;
    }

    _state.reset(true);

    // chords
    for (uint8_t i = 0; i < NB_CHORDS; i++)
    {
        for (uint8_t j = 0; j < NB_NOTES_PER_CHORD; j++)
        {
            _state._chords[i][j] = EEPROM.read(idx++);
        }
    }

    // chord selections
    for (uint8_t c = 0; c < NB_CHANNELS; c++)
    {
        for (uint8_t i = 0; i < NB_CHORD_BARS; i++)
        {
            for (uint8_t j = 0; j < NB_CHORDS_PER_BAR; j++)
            {
                _state._chordSel[c][i][j] = EEPROM.read(idx++);
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
                _state._notesSel[c][i][j] = EEPROM.read(idx++);
                _state._trigs[c][i][j] = EEPROM.read(idx++);
            }
        }
    }

    // transpositions
    for (uint8_t c = 0; c < NB_CHANNELS; c++)
    {
        _state._transpose[c] = EEPROM.read(idx++);
    }

    return true;
}