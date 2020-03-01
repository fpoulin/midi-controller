#define ARDUINO 1000
#include "Gui.h"
#include "MidiIo.h"
#include "State.h"
#include "SyncPulse.h"

State _state;
Gui _gui(_state);
SyncPulse _syncPulse;

void playStep(uint8_t step, void (*sendNote)(uint8_t channel, uint8_t *notes));
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
    _syncPulse.setup();
}

void loop()
{
    midiIo::loop();
    _syncPulse.loop();
}

void playStep(uint8_t step, void (*sendNote)(uint8_t channel, uint8_t *notes))
{
    if (step % 2 == 0)
    {
        _syncPulse.sendPulse();
    }
    
    _state.moveToStep(step);
    _gui.moveToStep(step);

    for (uint8_t channel = 0; channel < 2; channel++)
    {
        if (_state.hasTrigOn(channel) != 0)
        {
            sendNote(channel, _state.getNotes(channel));
        }
    }
}

void addChord(uint8_t *chord)
{
    _state.addChord(chord);
}

void stop()
{
    _state.reset();
    _gui.reset();
    _syncPulse.reset();
}