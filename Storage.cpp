#include "Storage.h"
#include <arduino.h>
#include <EEPROM.h>
#include "MidiIo.h"

#define STORAGE_SETTINGS_SPACE_SHIFT 5
#define STORAGE_SETTINGS_VERSION 1

Storage::Storage(State &state) : _state(state)
{
    restoreState();
    restoreSettings();
}

void Storage::writeState()
{
    int idx = STORAGE_SETTINGS_SPACE_SHIFT;

    EEPROM.update(idx++, STORAGE_STATE_VERSION);

    // chords
    for (uint8_t i = 0; i < NB_CHORDS; i++)
    {
        for (uint8_t j = 0; j < NB_NOTES_PER_CHORD; j++)
        {
            EEPROM.update(idx++, _state._chords[i][j]);
        }
    }

    // chord selections
    for (uint8_t i = 0; i < NB_CHORD_BARS; i++)
    {
        for (uint8_t j = 0; j < NB_CHORDS_PER_BAR; j++)
        {
            EEPROM.update(idx++, _state._chordSel[i][j]);
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
    int idx = STORAGE_SETTINGS_SPACE_SHIFT;

    uint8_t version = EEPROM.read(idx++);
    if (version != STORAGE_STATE_VERSION)
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
    for (uint8_t i = 0; i < NB_CHORD_BARS; i++)
    {
        for (uint8_t j = 0; j < NB_CHORDS_PER_BAR; j++)
        {
            _state._chordSel[i][j] = EEPROM.read(idx++);
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

void Storage::writeSettings()
{
    int idx = 0;

    EEPROM.update(idx++, STORAGE_SETTINGS_VERSION);
    EEPROM.update(idx++, midiIo::getMidiChannelIn());
    EEPROM.update(idx++, midiIo::getMidiChannelOut(0));
    EEPROM.update(idx++, midiIo::getMidiChannelOut(1));
    EEPROM.update(idx++, 0); // reserved
}

bool Storage::restoreSettings()
{
    int idx = 0;

    uint8_t version = EEPROM.read(idx++);
    if (version != STORAGE_SETTINGS_VERSION)
    {
        return false;
    }

    midiIo::setMidiChannelIn(EEPROM.read(idx++));
    midiIo::setMidiChannelOut(0, EEPROM.read(idx++));
    midiIo::setMidiChannelOut(1, EEPROM.read(idx++));

    return true;
}