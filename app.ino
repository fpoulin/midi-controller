#define ARDUINO 1000
#include "Screen.h"

Screen screen;

/* MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

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
  MIDI.sendNoteOn(note - 1, 0, 1);
} */

void setup()
{
  Serial.begin(9600);

  /*
  pinMode(A1, INPUT); // linear
  pinMode(A2, INPUT); // knob 4
  pinMode(A3, INPUT); // knob 3
  pinMode(A4, INPUT); // knob 2
  pinMode(A5, INPUT); // knob 1

  pinMode(PIN2, INPUT_PULLUP); // push 1
  pinMode(PIN3, INPUT_PULLUP); // push 2
  pinMode(PIN4, INPUT_PULLUP); // push 3

  MIDI.begin(MIDI_CHANNEL_OMNI); // Listen to all incoming messages
  MIDI.turnThruOff();
  MIDI.setHandleClock(handleClock);
  MIDI.setHandleStart(handleStart);
  MIDI.setHandleContinue(handleContinue);
  MIDI.setHandleStop(handleStop);
   */
}

// the current step
int step = 0;

void loop()
{
  // MIDI.read();

  screen.display(step);
  int oldStep = step;

  delay(50);
  step = ++step % 64;

  screen.clear(oldStep);
}