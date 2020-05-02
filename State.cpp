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
    uint8_t shifted = step >= _trigNudges[channel]
        ? step - _trigNudges[channel]
        : step + 32 - _trigNudges[channel];

    return _trigs[channel][getBar(shifted) % NB_NOTES_BARS][getTrig(shifted)];
}

bool State::isChordSelected(uint8_t step, uint8_t channel, uint8_t chordSelectionId)
{
    uint8_t shiftedChord = step >= _chordNudges[0] * NB_CHORDS_PER_BAR
        ? step - _chordNudges[0] * NB_CHORDS_PER_BAR
        : step + 128 - _chordNudges[0] * NB_CHORDS_PER_BAR;

    uint8_t chordSel = _chordSel[channel][getBar(shiftedChord) % NB_CHORD_BARS][getBeat(shiftedChord)];
    uint8_t shiftedChordSel = (chordSel + _chordNudges[1]) % NB_CHORDS;

    return shiftedChordSel == chordSelectionId;
}

bool State::isNoteSelected(uint8_t step, uint8_t channel, uint8_t noteSelectionId)
{
    uint8_t shifted = step >= _noteNudges[channel][0]
        ? step - _noteNudges[channel][0]
        : step + 32 - _noteNudges[channel][0];

    uint8_t notesSel = _notesSel[channel][getBar(shifted) % NB_NOTES_BARS][getTrig(shifted)];

    // bitmap -> first X bits are the notes selected within the chord
    return _notesToPlay[noteSelectionId] = ((128 >> (noteSelectionId + NB_NOTES_PER_CHORD - _noteNudges[channel][1]) % NB_NOTES_PER_CHORD) & notesSel) != 0;
}

uint8_t *State::getNotes(uint8_t step, uint8_t channel)
{
    uint8_t shiftedChord = step > _chordNudges[0] * NB_CHORDS_PER_BAR
        ? step - _chordNudges[0] * NB_CHORDS_PER_BAR
        : step + 128 - _chordNudges[0] * NB_CHORDS_PER_BAR;

    uint8_t chordSel = _chordSel[channel][getBar(shiftedChord) % NB_CHORD_BARS][getBeat(shiftedChord)];
    uint8_t shiftedChordSel = (chordSel + _chordNudges[1]) % NB_CHORDS;

    for (uint8_t i = 0; i < NB_NOTES_PER_CHORD; i++)
    {
        _notesToPlay[i] = isNoteSelected(step, channel, i)
            ? _chords[shiftedChordSel][i] + (_transpose[channel] - 2) * 12
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

void State::setChordNudge(uint8_t amount, bool horizontal)
{
    _chordNudges[horizontal ? 0 : 1] = amount;
}

void State::setNotesNudge(uint8_t channel, uint8_t amount, bool horizontal)
{
    _noteNudges[channel][horizontal ? 0 : 1] = amount;
}

void State::setTrigNudge(uint8_t channel, uint8_t amount)
{
    _trigNudges[channel] = amount;
}

void State::applyAllNudges()
{
    uint8_t shiftedIndex;
    uint8_t *ptr;

    // chords
    if(_chordNudges[0] != 0 || _chordNudges[1] != 0)
    {
        for (uint8_t i = 0; i < 32; i++)
        {
            ptr = &_chordSel[0][getBar(i * 4) % NB_CHORD_BARS][getBeat(i * 4)];
            _nudgeBuffer[i] = *ptr;

            // read forward as long as possible, then read from buffer
            shiftedIndex = (i + 32 - _chordNudges[0]) % 32;
            *ptr = i + _chordNudges[0] < 32
                ? _chordSel[0][getBar(shiftedIndex * 4) % NB_CHORD_BARS][getBeat(shiftedIndex * 4)]
                : _nudgeBuffer[i - (32 - _chordNudges[0])];

            *ptr = (*ptr + _chordNudges[1]) % NB_CHORDS;
        }
    }

    // channels
    for (uint8_t channel = 0; channel < NB_CHANNELS; channel++)
    {
        // notes
        if(_noteNudges[channel][0] != 0 || _noteNudges[channel][1] != 0)
        {
            for (uint8_t i = 0; i < 32; i++)
            {
                ptr = &_notesSel[channel][getBar(i) % NB_NOTES_BARS][getTrig(i)];
                _nudgeBuffer[i] = *ptr;

                // read forward as long as possible, then read from buffer
                shiftedIndex = (i + 32 - _noteNudges[channel][0]) % 32;
                *ptr = i + _noteNudges[channel][0] < 32
                    ? _notesSel[channel][getBar(shiftedIndex) % NB_NOTES_BARS][getTrig(shiftedIndex)]
                    : _nudgeBuffer[i - (32 - _noteNudges[channel][0])];

                // ex: for 10010000, nudge = 2: (00100100 | 01000000) & 11110000 = 01100000
                *ptr = (*ptr >> _noteNudges[channel][1] | *ptr << (4 - _noteNudges[channel][1])) & B11110000;
            }
        }
        
        // trigs
        if(_trigNudges[channel] != 0) 
        {
            for (uint8_t i = 0; i < 32; i++)
            {
                ptr = &_trigs[channel][getBar(i) % NB_NOTES_BARS][getTrig(i)];
                _nudgeBuffer[i] = *ptr;

                // read forward as long as possible, then read from buffer
                shiftedIndex = (i + 32 - _trigNudges[channel]) % 32;
                *ptr = i + _trigNudges[channel] < 32
                    ? _trigs[channel][getBar(shiftedIndex) % NB_NOTES_BARS][getTrig(shiftedIndex)]
                    : _nudgeBuffer[i - (32 - _trigNudges[channel])];
            }
        }
    }

    resetAllNudges();
}

void State::resetAllNudges() {

    _chordNudges[0] = 0;
    _chordNudges[1] = 0;

    for (uint8_t i = 0; i < NB_CHANNELS; i++)
    {
        _noteNudges[i][0] = 0;
        _noteNudges[i][1] = 0;
        _trigNudges[i] = 0;
    }
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