#define ARDUINO 1000
#include "Screen.h"
#include "MidiIo.h"
#include "State.h"

ui::Screen screen;
core::State state;
int _lastStep = 0;

void playStep(const int &step, void (*sendNote)(const byte &note));

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
}

void playStep(const int &step, void (*sendNote)(const byte &note))
{
    state.setStep(step);

    // play note
    if (state.hasNote())
    {
        sendNote(state.getNote());
    }

    // dmt
    screen.clear(_lastStep);
    screen.display(step);
    _lastStep = step;
}