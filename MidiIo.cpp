//#define DEBUG_SERIAL 1

#include <MIDI.h>
#include "MidiIo.h"

BEGIN_MIDI_IO_NAMESPACE

void handleClock(void);
void handleStart(void);
void handleContinue(void);
void handleStop(void);
void sendNote(const byte &note);

#ifndef DEBUG_SERIAL
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);
#endif

bool _playing = false;
unsigned long _ticks = 0;
int _count = 0;
byte lastNote;

void (*_onStep)(const int &step, void (*sendNote)(const byte &note));

void init(void (*onStep)(const int &step, void (*sendNote)(const byte &note)))
{
    _onStep = onStep;

#ifdef DEBUG_SERIAL
    Serial.begin(9600);
    Serial.println("Starting in debug ...");
    Serial.flush();
#else

    MIDI.begin();
    MIDI.turnThruOff();
    Serial.flush();
    MIDI.setHandleClock(handleClock);
    MIDI.setHandleStart(handleStart);
    MIDI.setHandleContinue(handleContinue);
    MIDI.setHandleStop(handleStop);
#endif
}

void doTheThing()
{
    _onStep(_count, sendNote);
    _count++;
}

void sendNote(const byte &note)
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

#ifdef DEBUG_SERIAL
    Serial.print("Note off: ");
    Serial.print(lastNote);
#else
    MIDI.sendNoteOn(lastNote, 0, 1);
#endif
}

END_MIDI_IO_NAMESPACE