#define ARDUINO 1000
// #include <MIDI.h>
#include <LedControl.h>
#include <binary.h>

// init dot matrix display
LedControl dmt1 = LedControl(11, 9, 10, 4);
LedControl dmt2 = LedControl(8, 6, 7, 4);

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

  // init screen
  for (int address = 0; address < dmt1.getDeviceCount(); address++)
  {
    dmt1.shutdown(address, false);
    dmt1.setIntensity(address, 0);
    dmt1.clearDisplay(address);
  }

  for (int address = 0; address < dmt2.getDeviceCount(); address++)
  {
    dmt2.shutdown(address, false);
    dmt2.setIntensity(address, 0);
    dmt2.clearDisplay(address);
  }

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

unsigned char trigs[8] = {
    r(0b00000000),
    r(0b01100110),
    r(0b01100110),
    r(0b00000000),
    r(0b00011000),
    r(0b00011000),
    r(0b01000010),
    r(0b00111100)
  };

void loop()
{
  // MIDI.read();

  LedControl dmt = step < 32 ? dmt1 : dmt2;
  int bar = step % 32 / 8;
  int col = step % 8;

  for (int row = 0; row < 8; row++)
  {
    byte leds = trigs[7-row]; // swap row vertically ...
    leds = leds | 0x1 << col;
    dmt.setRow(bar, row, leds);
  }

  // for now, just wait and then move to next step
  delay(50);
  step = ++step % 64;

  // clear the module
  for (int row = 0; row < 8; row++)
  {
    dmt.setRow(bar, row, 0);
  }
}

// swap col horizontally...
unsigned char r(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}