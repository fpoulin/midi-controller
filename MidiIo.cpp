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
uint8_t lastNote;

uint8_t nbKeyPressed = 0;
uint8_t chord[4];
bool sendChord = false;

void (*_onStep)(int step, void (*sendNote)(byte note));
void (*_onChord)(byte *chord);
void (*_onStop)(void);

void init(
    void (*onStep)(int step, void (*sendNote)(byte note)),
    void (*onChord)(byte *chord),
    void (*onStop)(void))
{
    _onStep = onStep;
    _onChord = onChord;
    _onStop = onStop;

    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();
    MIDI.setHandleClock(handleClock);
    MIDI.setHandleStart(handleStart);
    MIDI.setHandleStop(handleStop);
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
}

void sendNote(uint8_t note)
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
    nbKeyPressed = 0;
    sendChord = false;
    _onStop();

    MIDI.sendNoteOn(lastNote, 0, 1);
}

void handleNoteOn(byte channel, byte note, byte velocity)
{
    if (nbKeyPressed < 4)
    {
        chord[nbKeyPressed++] = note;
        if (nbKeyPressed == 4)
        {
            sendChord = true;
        }
    }
}

void handleNoteOff(byte channel, byte note, byte velocity)
{
    if (!--nbKeyPressed && sendChord)
    {
        _onChord(chord);
    }
}

END_MIDI_IO_NAMESPACE