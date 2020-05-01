#include "State.h"

State::State()
{
    uint8_t scale[] = {48, 50, 51, 53, 55, 56, 58, 60}; // c minor
    uint8_t scaleSize = 8;

    // quick and dirty (assumes 4 notes per chord)
    for (uint8_t i = 0; i < 4; i++)
    {
        _chords[i][0] = scale[i % scaleSize];
        _chords[i][1] = scale[(i + 2) % scaleSize];
        _chords[i][2] = _chords[i][0] + 12;
        _chords[i][3] = _chords[i][1] + 12;
    }

    reset(false);
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
    return _trigs[channel][getBar(step) % NB_NOTES_BARS][getTrig(step)];
}

bool State::isChordSelected(uint8_t step, uint8_t channel, uint8_t chordSelectionId)
{
    return _chordSel[channel][getBar(step) % NB_CHORD_BARS][getBeat(step)] == chordSelectionId;
}

bool State::isNoteSelected(uint8_t step, uint8_t channel, uint8_t noteSelectionId)
{
    uint8_t notesSel = _notesSel[channel][getBar(step) % NB_NOTES_BARS][getTrig(step)];

    // bitmap -> first X bits are the notes selected within the chord
    return _notesToPlay[noteSelectionId] = ((128 >> noteSelectionId) & notesSel) != 0;
}

uint8_t *State::getNotes(uint8_t step, uint8_t channel)
{
    uint8_t choordSel = _chordSel[channel][getBar(step) % NB_CHORD_BARS][getBeat(step)];

    for (uint8_t i = 0; i < NB_NOTES_PER_CHORD; i++)
    {
        _notesToPlay[i] =
            isNoteSelected(step, channel, i)
                ? _chords[choordSel][i] + (_transpose[channel] - 2) * 12
                : 0;
    }

    return _notesToPlay;
}

void State::addChord(uint8_t *chord)
{
    for (uint8_t i = 0; i < NB_NOTES_PER_CHORD; i++)
    {
        _chords[_currChordInputId][i] = chord[i];
    }
    _currChordInputId = ++_currChordInputId % NB_NOTES_PER_CHORD;
}

void State::setTrig(uint8_t step, uint8_t channel, bool state)
{
    // triggers on: [channel][bar%2][trig]
    _trigs[channel][getBar(step) % NB_NOTES_BARS][getTrig(step)] = state ? 127 : 0;
}

void State::setChordSelected(uint8_t step, uint8_t chordSelectionId)
{
    // selection of a chord: [channel][bar%8][beat]
    _chordSel[0][getBar(step) % NB_CHORD_BARS][getBeat(step)] = chordSelectionId;
    _chordSel[1][getBar(step) % NB_CHORD_BARS][getBeat(step)] = chordSelectionId;
}

void State::setNoteSelected(uint8_t step, uint8_t channel, uint8_t noteSelectionId, bool state)
{
    // selection of notes: [channel][bar%2][trig]
    uint8_t mask = 128 >> noteSelectionId;
    if (state)
    {
        _notesSel[channel][getBar(step) % NB_NOTES_BARS][getTrig(step)] |= mask;
    }
    else
    {
        _notesSel[channel][getBar(step) % NB_NOTES_BARS][getTrig(step)] &= ~mask;
    }
}

void State::setTranspose(uint8_t channel, uint8_t octave)
{
    _transpose[channel] = octave;
}

void State::reset(bool soft)
{
    _currChordInputId = 0;

    if (soft)
    {
        return;
    }

    randomSeed(millis());

    // chords selections
    for (uint8_t i = 0; i < NB_CHORD_BARS; i++)
    {
        for (uint8_t j = 0; j < NB_CHORDS_PER_BAR; j++)
        {
            _chordSel[0][i][j] = i / 2;
            _chordSel[1][i][j] = i / 2;
        }
    }

    // notes selections and trigs
    for (uint8_t i = 0; i < NB_NOTES_BARS; i++)
    {
        for (uint8_t j = 0; j < NB_NOTES_PER_BAR; j++)
        {
            // channel 1
            _notesSel[0][i][j] = 128 >> random(0, NB_NOTES_PER_CHORD);
            _trigs[0][i][j] = 127;

            // channel 2
            if (j % 4 == 0)
            {
                _notesSel[1][i][j] = 192; // 1100000
                _trigs[1][i][j] = 127;
            }
            else if (j % 3 == 0)
            {
                _notesSel[1][i][j] = 48; // 00110000
                _trigs[1][i][j] = 127;
            }
            else
            {
                _notesSel[1][i][j] = 128;
                _trigs[1][i][j] = 0;
            }
        }
    }

    // transpose (setting octave nb, starting at -2)
    for (uint8_t c = 0; c < NB_CHANNELS; c++)
    {
        _transpose[c] = 0;
    }
}