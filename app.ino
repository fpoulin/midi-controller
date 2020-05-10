#define ARDUINO 1000
#include "MidiIo.h"
#include "State.h"
#include "Storage.h"
#include "Gui.h"
#include "SyncPulse.h"
#include "Controls.h"
#include "ModesManager.h"

State _state;
Storage _storage(_state);
Gui _gui(_state);
SyncPulse _syncPulse;
Controls _controls;
ModesManager _modes(_gui, _state, _storage, _controls);

void playStep(uint8_t step, void (*sendNote)(uint8_t channel, uint8_t *notes));
void handleChord(uint8_t *chord, uint8_t nbNotes);
void stop();

void setup()
{
    midiIo::init(playStep, handleChord, stop);
    _syncPulse.setup();
}

void loop()
{
    midiIo::loop();
    _syncPulse.loop();
    _controls.loop();
    _gui.loop();
}

void playStep(uint8_t step, void (*sendNote)(uint8_t channel, uint8_t *notes))
{
    if (step % 2 == 0)
    {
        _syncPulse.sendPulse();
    }

    for (uint8_t channel = 0; channel < NB_CHANNELS; channel++)
    {
        if (_state.hasTrigOn(step, channel, false) != 0)
        {
            sendNote(channel, _state.getNotes(step, channel));
        }
    }

    _gui.renderStep(step);
}

void handleChord(uint8_t *chord, uint8_t nbNotes)
{
    _gui.handleChordIn(chord, nbNotes);
}

void stop()
{
    _state.reset(true);
    _syncPulse.reset();
    _gui.redraw(true);
}