#define ARDUINO 1000
#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

bool playing = false;
int ticks = 0;
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
  MIDI.sendNoteOn(note, 127, 1);
  MIDI.sendNoteOn(note-1, 0, 1);
}

void setup()
{
  MIDI.begin(MIDI_CHANNEL_OMNI); // Listen to all incoming messages
  MIDI.turnThruOff();
  MIDI.setHandleClock(handleClock);
  MIDI.setHandleStart(handleStart);
  MIDI.setHandleContinue(handleContinue);
  MIDI.setHandleStop(handleStop);
}

void loop()
{
  MIDI.read();
}