#define ARDUINO 1000
#include "Screen.h"
#include "MidiIo.h"
#include "State.h"

Screen screen;
State state;

void playStep(int step, void (*sendNote)(byte note));
void addNote(byte note);
void stop();

void setup()
{
    pinMode(A1, INPUT); // linear

    pinMode(A2, INPUT); // knob 4
    pinMode(A3, INPUT); // knob 3
    pinMode(A4, INPUT); // knob 2
    pinMode(A5, INPUT); // knob 1

    pinMode(PIN2, INPUT_PULLUP); // push 1
    pinMode(PIN3, INPUT_PULLUP); // push 2
    pinMode(PIN4, INPUT_PULLUP); // push 3

    midiIo::init(playStep, addNote, stop);
}

void loop()
{
    midiIo::loop();
}

void playStep(int step, void (*sendNote)(byte note))
{
    screen.moveCursor(step);

    state.moveToStep(step);
    if (state.hasNote())
    {
        sendNote(state.getNote());
    }
}

void addNote(byte note)
{
    state.addNote(note);
}

void stop()
{
    screen.moveCursor(0);
    state.reset();
}