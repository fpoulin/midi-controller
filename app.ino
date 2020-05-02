#define ARDUINO 1000
#include "Gui.h"
#include "MidiIo.h"
#include "State.h"
#include "Storage.h"
#include "SyncPulse.h"
#include "Controls.h"
#include "PushButton.h"
#include "ModePerform.h"

State _state;
Storage _storage(_state);
Gui _gui(_state);
SyncPulse _syncPulse;
Controls _controls;
ModePerform _modePerform(_controls, _gui, _state);

uint8_t _mode = 0;

void playStep(uint8_t step, void (*sendNote)(uint8_t channel, uint8_t *notes));
void addChord(uint8_t *chord);
void stop();

void setup()
{
    midiIo::init(playStep, addChord, stop);

    _storage.restoreState();
    _syncPulse.setup();
    _modePerform.Activate();
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

    for (uint8_t channel = 0; channel < 2; channel++)
    {
        if (_state.hasTrigOn(step, channel) != 0)
        {
            sendNote(channel, _state.getNotes(step, channel));
        }
    }

    _gui.renderStep(step);
}

void addChord(uint8_t *chord)
{
    _state.addChord(chord);
}

void stop()
{
    _state.reset(true);
    _gui.reset();
    _syncPulse.reset();
}