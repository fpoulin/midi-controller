#define ARDUINO 1000
#include "Screen.h"
#include "MyMidi.h"

Screen screen;

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

    setupMidi();
}

// the current step
int step = 0;

void loop()
{
    loopMidi();

    screen.display(step);
    int oldStep = step;

    delay(20);
    step = ++step % 64;

    screen.clear(oldStep);
}