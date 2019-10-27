#pragma once

class State
{
private:
    unsigned char _currBeat; // 0-8
    unsigned char _currTrig; // 128, 64, 32, 16, 8, 4, 2, 1
    unsigned char _currNote; // 0-4

    unsigned char _currNoteId; // 0-4

    unsigned char _trigs[8];
    unsigned char _notes[4];

public:
    State();
    void addNote(unsigned char note);
    void moveToStep(int step);
    bool hasNote();
    unsigned char getNote();
    void reset();
};