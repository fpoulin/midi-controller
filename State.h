#include <arduino.h>

#pragma once

class State
{
private:
    uint8_t _currChordInputId; // 0-4

    uint8_t _currStep; // 0-255
    uint8_t _currBar;  // 0-8
    uint8_t _currBeat; // 0-4
    uint8_t _currTrig; // 0-16

    uint8_t _chords[4][4];       // 4 chords of 4 notes
    uint8_t _chordSel[2][8][4];  // selection of a chord: [channel][bar][beat]
    uint8_t _notesSel[2][2][16]; // selection of notes: [channel][bar][trig]
    uint8_t _trigsOn[2][2][16];  // triggers on: [channel][bar][trig]
    boolean _trigsOff[2][2][16]; // triggers off: [channel][bar][trig]
    int8_t _transpose[2];        // transpose semi-tones: [channel]

    uint8_t _notesToPlay[4]; // buffer for notes to be played

public:
    State();
    void addChord(uint8_t *chord);
    void moveToStep(uint8_t step);
    uint8_t hasTrigOn(uint8_t channel);
    boolean hasTrigOff(uint8_t channel);
    bool isNoteSelected(uint8_t channel, uint8_t noteSelection);
    uint8_t *getNotes(uint8_t channel);
    void reset();
};