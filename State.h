#pragma once

#define BEGIN_STATE_NAMESPACE \
    namespace core            \
    {
#define END_STATE_NAMESPACE }

BEGIN_STATE_NAMESPACE

class State
{
private:
    unsigned char _currBeat; // 0-8
    unsigned char _currTrig; // 128, 64, 32, 16, 8, 4, 2, 1
    unsigned char _currNote; // 0-4

    unsigned char trigs[8];
    unsigned char notes[4];

public:
    State();
    void setStep(int step);
    bool hasNote();
    unsigned char getNote();
};

END_STATE_NAMESPACE