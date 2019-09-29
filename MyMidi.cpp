#define DEBUG_SERIAL 1

#include <MIDI.h>
#include "MyMidi.h"

#ifndef DEBUG_SERIAL
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);
#endif

bool playing = false;
unsigned long ticks = 0;
int count = 0;

void handleClock(void)
{
    if (playing && ticks++ % 6 == 0)
    {
        doTheThing();
    }
}

void handleStart(void)
{
    playing = true;
    ticks = 0;
    count = 0;
}

void handleContinue(void)
{
    playing = true;
    ticks = 0;
}

void handleStop(void)
{
    playing = false;
    ticks = 0;
}

void doTheThing()
{
    int note = count++ % 16 + 36;
    
    #ifdef DEBUG_SERIAL
    Serial.print("Note on: ");
    Serial.println(note);
    Serial.flush();
    #else
    MIDI.sendNoteOn(note, 127, 1);
    MIDI.sendNoteOn(note - 1, 0, 1);
    #endif
}

void setupMidi() {
    #ifdef DEBUG_SERIAL
    Serial.begin(9600);
    Serial.println("Starting in debug ...");
    Serial.flush();
    #else
    Serial.flush();
    Serial.begin(31250);
    MIDI.begin(MIDI_CHANNEL_OMNI); // Listen to all incoming messages
    MIDI.turnThruOff();
    MIDI.setHandleClock(handleClock);
    MIDI.setHandleStart(handleStart);
    MIDI.setHandleContinue(handleContinue);
    MIDI.setHandleStop(handleStop);
    #endif
}

void loopMidi()
{
    #ifdef DEBUG_SERIAL
    unsigned long t = millis();
    if (t - ticks > 1000) {
        ticks = t;
        doTheThing();
    }
    #else
    MIDI.read();
    #endif
}
