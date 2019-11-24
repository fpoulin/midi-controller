#define ARDUINO 1000
#include "Screen.h"
#include "MidiIo.h"
#include "State.h"

Screen screen;
State state;

void playStep(int step, void (*sendNote)(uint8_t channel, uint8_t *notes));
void addChord(uint8_t *chord);
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

    midiIo::init(playStep, addChord, stop);
}

void loop()
{
    midiIo::loop();
}

void playStep(int step, void (*sendNote)(uint8_t channel, uint8_t *notes))
{
    screen.moveCursor(step);
    state.moveToStep(step);

    for (uint8_t channel = 0; channel < 2; channel++)
    {
        if (state.hasTrigOn(channel) != 0)
        {
            sendNote(channel, state.getNotes(channel));
        }
    }
}

void addChord(uint8_t *chord)
{
    state.addChord(chord);
}

void stop()
{
    screen.moveCursor(0);
    state.reset();
}