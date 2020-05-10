#include "State.h"
#include "MidiIo.h"

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

uint8_t State::hasTrigOn(uint8_t step, uint8_t channel, bool skipProbability)
{
    // randombly add more trigs
    if(!skipProbability && _trigProbability[channel] > random(100, 200))
    {
        return 127;
    }

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

    uint8_t chordSel = _chordSel[getBar(shiftedChord) % NB_CHORD_BARS][getBeat(shiftedChord)];
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
    // randomly remove some trigs by playing empty notes (i.e. send a note off for what's playing)
    if(_trigProbability[channel] < random(0, 100))
    {
        for (uint8_t i = 0; i < NB_NOTES_PER_CHORD; i++)
        {
            _notesToPlay[i] = 0;
        }

        return _notesToPlay;
    }

    uint8_t shiftedChord = step > _chordNudges[0] * NB_CHORDS_PER_BAR
        ? step - _chordNudges[0] * NB_CHORDS_PER_BAR
        : step + 128 - _chordNudges[0] * NB_CHORDS_PER_BAR;

    uint8_t chordSel = _chordSel[getBar(shiftedChord) % NB_CHORD_BARS][getBeat(shiftedChord)];
    uint8_t shiftedChordSel = (chordSel + _chordNudges[1]) % NB_CHORDS;

    for (uint8_t i = 0; i < NB_NOTES_PER_CHORD; i++)
    {
        _notesToPlay[i] = isNoteSelected(step, channel, i) && !_mute[channel]
            ? _chords[shiftedChordSel][i] + (_transpose[channel] - 2) * 12
            : 0;
    }

    return _notesToPlay;
}

void State::setTrig(uint8_t step, uint8_t channel, bool state)
{
    // triggers on: [channel][bar%2][trig]
    _trigs[channel][getBar(step) % NB_NOTES_BARS][getTrig(step)] = state ? 127 : 0;
}

void State::setChordSelected(uint8_t step, uint8_t chordSelectionId)
{
    // selection of a chord: [channel][bar%8][beat]
    _chordSel[getBar(step) % NB_CHORD_BARS][getBeat(step)] = chordSelectionId;
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

void State::setSwag(uint8_t channel, uint8_t swagValue) // 0-10
{
    if(swagValue < 4)
    {
        _trigProbability[channel] = map(swagValue, 0, 3, 5, 90);
    }
    else if(swagValue < 7)
    {
        _trigProbability[channel] = 100;
    }
    else
    {
        _trigProbability[channel] = map(swagValue, 7, 10, 110, 200);
    }
}

void State::resetAllSwags()
{
    for (uint8_t i = 0; i < NB_CHANNELS; i++)
    {
        _trigProbability[i] = 100;
    }
}

void State::setTranspose(uint8_t channel, uint8_t octave)
{
    _transpose[channel] = octave;
}

void State::toggleMuteChannel(uint8_t channel)
{
    _mute[channel] = !_mute[channel];
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
            ptr = &_chordSel[getBar(i * 4) % NB_CHORD_BARS][getBeat(i * 4)];
            _nudgeBuffer[i] = *ptr;

            shiftedIndex = i > _chordNudges[0]
                ? i - _chordNudges[0]
                : i + 32 - _chordNudges[0];

            // read forward as long as possible, then read from buffer
            *ptr = i < _chordNudges[0]
                ? _chordSel[getBar(shiftedIndex * 4) % NB_CHORD_BARS][getBeat(shiftedIndex * 4)]
                : _nudgeBuffer[i - _chordNudges[0]];

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

                shiftedIndex = i > _noteNudges[channel][0]
                    ? i - _noteNudges[channel][0]
                    : i + 32 - _noteNudges[channel][0];

                // read forward as long as possible, then read from buffer
                *ptr = i < _noteNudges[channel][0]
                    ? _notesSel[channel][getBar(shiftedIndex) % NB_NOTES_BARS][getTrig(shiftedIndex)]
                    : _nudgeBuffer[i - _noteNudges[channel][0]];

                // vertical nudge: for 10010000 and nudge = 2: (00100100 | 01000000) & 11110000 = 01100000
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

                shiftedIndex = i > _noteNudges[channel][0]
                    ? i - _noteNudges[channel][0]
                    : i + 32 - _noteNudges[channel][0];

                // read forward as long as possible, then read from buffer
                *ptr = i < _trigNudges[channel]
                    ? _trigs[channel][getBar(shiftedIndex) % NB_NOTES_BARS][getTrig(shiftedIndex)]
                    : _nudgeBuffer[i - _trigNudges[channel]];
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

void State::setHandleChordMode(uint8_t mode)
{
    _handleChordMode = mode;

    switch (_handleChordMode)
    {
    // setup 'store chord' mode
    case 1:
        midiIo::setChordYieldMinimum(4);
        resetChordInputId();
        break;
    
    // setup 'set ref notes' mode
    case 2:
        midiIo::setChordYieldMinimum(4);
        break;

    // setup 'step edit' mode
    case 3:
        midiIo::setChordYieldMinimum(1);
        _stepEditAtStep = 0;
        break;

    // otherwise just silence the MIDI in
    default:
        midiIo::setChordYieldMinimum(0);
        break;
    }
}

void State::handleChord(uint8_t *chord, uint8_t nbNotes, uint8_t destination)
{
    switch (_handleChordMode)
    {
    // store chord
    case 1:
        for (uint8_t i = 0; i < NB_NOTES_PER_CHORD; i++)
        {
            _chords[_currChordInputId][i] = chord[i];
        }
        _currChordInputId = ++_currChordInputId % NB_NOTES_PER_CHORD;
        break;

    // set ref notes (and switch to step edit)
    case 2:
        for (uint8_t i = 0; i < NB_NOTES_PER_CHORD; i++)
        {
            _refNotes[i] = chord[i];
        }
        setHandleChordMode(3);
        break;

    // step edit
    case 3:
        
        uint8_t bitmap;
        bool found;

        switch(destination)
        {
            // chord selection
            case 0:
                for (uint8_t i = 0; i < NB_NOTES_PER_CHORD; i++)
                {
                    if(_refNotes[i] == chord[0]) {
                        _chordSel[getBar(_stepEditAtStep * 4) % NB_CHORD_BARS][getBeat(_stepEditAtStep * 4)] = i;
                    }
                }
                break;

            // ch1 notes
            case 1:
                bitmap = 0;
                for (uint8_t i = 0; i < NB_NOTES_PER_CHORD; i++)
                {
                    for(uint8_t j = 0; j < nbNotes; j++)
                    {
                        if(_refNotes[i] == chord[j]) {
                            bitmap = 128 >> i | bitmap;
                        }
                    }
                }
                _notesSel[0][getBar(_stepEditAtStep) % NB_NOTES_BARS][getTrig(_stepEditAtStep)] = bitmap;
                break;

            // ch1: trigs
            case 2:
                found = false;
                for (uint8_t i = 0; i < NB_NOTES_PER_CHORD; i++)
                {
                    found |= _refNotes[i] == chord[0];
                }
                _trigs[0][getBar(_stepEditAtStep) % NB_NOTES_BARS][getTrig(_stepEditAtStep)] = found ? 127 : 0;
                break;

            // ch2 notes
            case 3:
                bitmap = 0;
                for (uint8_t i = 0; i < NB_NOTES_PER_CHORD; i++)
                {
                    for(uint8_t j = 0; j < nbNotes; j++)
                    {
                        if(_refNotes[i] == chord[j]) {
                            bitmap = 128 >> i | bitmap;
                        }
                    }
                }
                _notesSel[1][getBar(_stepEditAtStep) % NB_NOTES_BARS][getTrig(_stepEditAtStep)] = bitmap;
                break;

            // ch2 trigs
            case 4:
                found = false;
                for (uint8_t i = 0; i < NB_NOTES_PER_CHORD; i++)
                {
                    found |= _refNotes[i] == chord[0];
                }
                _trigs[1][getBar(_stepEditAtStep) % NB_NOTES_BARS][getTrig(_stepEditAtStep)] = found ? 127 : 0;
                break;
        }

        // auto-move forward
        _stepEditAtStep++;
        _stepEditAtStep = _stepEditAtStep % 32;
        break;
    }
}

void State::loopSteps(uint8_t destination)
{
    switch(destination)
    {
    // chord selection
    case 0:
        for (uint8_t i = _stepEditAtStep; i < 32; i++)
        {
            _chordSel[getBar(i * 4) % NB_CHORD_BARS][getBeat(i * 4)] = _chordSel[getBar((i-_stepEditAtStep) * 4) % NB_CHORD_BARS][getBeat((i-_stepEditAtStep) * 4)];
        }
        break;

    // ch1 notes
    case 1:
        for (uint8_t i = _stepEditAtStep; i < 32; i++)
        {
            _notesSel[0][getBar(i) % NB_NOTES_BARS][getTrig(i)] = _notesSel[0][getBar(i-_stepEditAtStep) % NB_NOTES_BARS][getTrig(i-_stepEditAtStep)];
        }
        break;

    // ch1: trigs
    case 2:
        for (uint8_t i = _stepEditAtStep; i < 32; i++)
        {
            _trigs[0][getBar(i) % NB_NOTES_BARS][getTrig(i)] = _trigs[0][getBar(i-_stepEditAtStep) % NB_NOTES_BARS][getTrig(i-_stepEditAtStep)];
        }
        break;

    // ch2 notes
    case 3:
        for (uint8_t i = _stepEditAtStep; i < 32; i++)
        {
            _notesSel[1][getBar(i) % NB_NOTES_BARS][getTrig(i)] = _notesSel[1][getBar(i-_stepEditAtStep) % NB_NOTES_BARS][getTrig(i-_stepEditAtStep)];
        }
        break;

    // ch2 trigs
    case 4:
        for (uint8_t i = _stepEditAtStep; i < 32; i++)
        {
            _trigs[1][getBar(i) % NB_NOTES_BARS][getTrig(i)] = _trigs[1][getBar(i-_stepEditAtStep) % NB_NOTES_BARS][getTrig(i-_stepEditAtStep)];
        }
        break;
    }
}

void State::resetChordInputId()
{
    _currChordInputId = 0;
}

void State::setStepEditAtStep(uint8_t step)
{
    _stepEditAtStep = step;
}

void State::reset(bool soft)
{
    resetChordInputId();

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
            _chordSel[i][j] = i / 2;
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