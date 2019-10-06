#define ARDUINO 1000
#include "Screen.h"
#include "MidiIo.h"
#include "State.h"

Screen screen;
State state;

void playStep (const int& step, void (*sendNote)(const byte& note));

// the current step
int step = 0;

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

    midiIo::init(playStep);
}

void loop()
{
    midiIo::loop();

    // screen.display(step);
    // int oldStep = step;
    // delay(20);
    // step = ++step % 64;
    // state.setState(step);
    // screen.clear(oldStep);
}

void playStep (const int& step, void (*sendNote)(const byte& note)) {
    int rand = step + random(2);
    byte note = rand % 16 + 36;
    sendNote(note);
}