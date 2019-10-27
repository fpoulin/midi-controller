#pragma once

class State
{
private:
    unsigned char _currTrig;         // 128, 64, 32, 16, 8, 4, 2, 1
    unsigned char _currBeat;         // 0-8
    unsigned char _currChord;        // 0-4
    unsigned char _currChordInputId; // 0-4
    unsigned char _currNote;         // 0-4

    unsigned char _trigs[4];
    unsigned char _chords[4][4];

public:
    State();
    void addChord(unsigned char* chord);
    void moveToStep(int step);
    bool hasNote();
    unsigned char getNote();
    void reset();
};