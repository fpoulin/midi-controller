#pragma once

class State
{
private:
    uint8_t _currTrig;         // 128, 64, 32, 16, 8, 4, 2, 1
    uint8_t _currBeat;         // 0-8
    uint8_t _currChord;        // 0-4
    uint8_t _currChordInputId; // 0-4
    uint8_t _currNote;         // 0-4

    uint8_t _trigs[4];
    uint8_t _chords[4][4];

public:
    State();
    void addChord(uint8_t* chord);
    void moveToStep(int step);
    bool hasNote();
    uint8_t getNote();
    void reset();
};