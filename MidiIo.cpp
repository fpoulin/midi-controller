#include <MIDI.h>
#include "MidiIo.h"

BEGIN_MIDI_IO_NAMESPACE

void handleClock();
void handleStart();
void handleStop();
void handleNoteOn(byte channel, byte note, byte velocity);
void handleNoteOff(byte channel, byte note, byte velocity);

midi::MidiInterface<HardwareSerial> MIDI((HardwareSerial &)Serial);

bool _playing = false;
unsigned long _ticks = 0;
int _step = 0;
byte lastNote;

void (*_onStep)(int step, void (*sendNote)(byte note));
void (*_onNote)(byte note);
void (*_onStop)(void);

void init(
    void (*onStep)(int step, void (*sendNote)(byte note)),
    void (*onNote)(byte note),
    void (*onStop)(void))
{
    _onStep = onStep;
    _onNote = onNote;
    _onStop = onStop;

    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();
    MIDI.setHandleClock(handleClock);
    MIDI.setHandleStart(handleStart);
    MIDI.setHandleStop(handleStop);
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
}

void sendNote(const byte note)
{
    MIDI.sendNoteOn(lastNote, 0, 1);
    MIDI.sendNoteOn(note, 127, 1);

    lastNote = note;
}

void loop()
{
    MIDI.read();
}

void handleClock()
{
    if (_playing && _ticks++ % 6 == 0)
    {
        _onStep(_step, sendNote);
        _step++;
    }
}

void handleStart()
{
    _playing = true;
}

void handleStop()
{
    _playing = false;
    _ticks = 0;
    _step = 0;
    _onStop();

    MIDI.sendNoteOn(lastNote, 0, 1);
}

void handleNoteOn(byte channel, byte note, byte velocity)
{
    /* do nothing for now */
}

void handleNoteOff(byte channel, byte note, byte velocity)
{
    _onNote(note);
}

END_MIDI_IO_NAMESPACE