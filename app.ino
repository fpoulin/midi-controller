#define ARDUINO 1000
#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

int count = 0;

void setup()
{
  MIDI.begin(MIDI_CHANNEL_OMNI); // Listen to all incoming messages
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  int note = count++ % 25 + 36;

  MIDI.sendNoteOn(note, 127, 1);
  delay(100);
  MIDI.sendNoteOn(note, 0, 1);
  delay(100);
}