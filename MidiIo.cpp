//#define DEBUG_SERIAL 1

#include <MIDI.h>
#include "MidiIo.h"

BEGIN_MIDI_IO_NAMESPACE

void handleClock(void);
void handleStart(void);
void handleContinue(void);
void handleStop(void);
void sendNote(const byte note);
void handleNoteOn(byte channel, byte note, byte velocity);
void handleNoteOff(byte channel, byte note, byte velocity);

#ifndef DEBUG_SERIAL
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);
#endif

bool _playing = false;
unsigned long _ticks = 0;
int _count = 0;
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

#ifdef DEBUG_SERIAL
    Serial.begin(9600);
    Serial.println("Starting in debug ...");
    Serial.flush();
#else

    MIDI.begin(MIDI_CHANNEL_OMNI);
    MIDI.turnThruOff();
    MIDI.setHandleClock(handleClock);
    MIDI.setHandleStart(handleStart);
    MIDI.setHandleContinue(handleContinue);
    MIDI.setHandleStop(handleStop);
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
#endif
}

void doTheThing()
{
    _onStep(_count, sendNote);
    _count++;
}

void sendNote(const byte note)
{

#ifdef DEBUG_SERIAL
    Serial.print("Note off: ");
    Serial.print(lastNote);
    Serial.print("  -- Note on: ");
    Serial.println(note);
    Serial.flush();
#else

    MIDI.sendNoteOn(lastNote, 0, 1);
    MIDI.sendNoteOn(note, 127, 1);
#endif

    lastNote = note;
}

void loop()
{
#ifdef DEBUG_SERIAL
    unsigned long t = millis();
    if (t - _ticks > 1000)
    {
        _ticks = t;
        doTheThing();
    }
#else
    MIDI.read();
#endif
}

void handleClock(void)
{
    if (_playing && _ticks++ % 6 == 0)
    {
        doTheThing();
    }
}

void handleStart(void)
{
    _playing = true;
    _ticks = 0;
    _count = 0;
}

void handleContinue(void)
{
    _playing = true;
    _ticks = 0;
}

void handleStop(void)
{
    _playing = false;
    _ticks = 0;
    _onStop();

#ifdef DEBUG_SERIAL
    Serial.print("Note off: ");
    Serial.print(lastNote);
#else
    MIDI.sendNoteOn(lastNote, 0, 1);
#endif
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