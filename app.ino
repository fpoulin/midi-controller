#define ARDUINO 1000
#include <MIDI.h>
#include <LedControl.h>

LedControl lc1 = LedControl(8, 6, 7, 4);
LedControl lc2 = LedControl(11, 9, 10, 4);

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
  MIDI.sendNoteOn(note - 1, 0, 1);
}

void setup()
{
  Serial.begin(9600);

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  pinMode(PIN2, INPUT_PULLUP);
  pinMode(PIN3, INPUT_PULLUP);
  pinMode(PIN4, INPUT_PULLUP);

  for (int address = 0; address < lc1.getDeviceCount(); address++)
  {
    lc1.shutdown(address, false);
    lc1.setIntensity(address, 8);
    lc1.clearDisplay(address);
  }

  for (int address = 0; address < lc2.getDeviceCount(); address++)
  {
    lc2.shutdown(address, false);
    lc2.setIntensity(address, 8);
    lc2.clearDisplay(address);
  }

  /*
  MIDI.begin(MIDI_CHANNEL_OMNI); // Listen to all incoming messages
  MIDI.turnThruOff();
  MIDI.setHandleClock(handleClock);
  MIDI.setHandleStart(handleStart);
  MIDI.setHandleContinue(handleContinue);
  MIDI.setHandleStop(handleStop);
   */
}

void loop()
{
  // MIDI.read();

  //read the number cascaded devices
  int devices = lc1.getDeviceCount();

  int count = 0;
  for (int i = 0; i < devices; i++)
  {
    int deviceNb = i;
    for (int j = 0; j < 8; j++)
    {
      int col = 7 - j;
      double radFactor = 3.1415926535 / 180;
      int row = floor((sin(radFactor * (i * 8 + 7 - col) / 32.0 * 360) + 1) / 2 * 7.99);

      lc1.setLed(deviceNb, row, col, true);
      lc2.setLed(deviceNb, row, col, true);

      int val = analogRead(A5);
      Serial.print(val);
      Serial.print(" - ");
      val = map(val, 185, 1023, 5, 100);
      Serial.println(val);

      if (digitalRead(PIN2) == HIGH)
      {
        val = val / 10;
      }
      else
      {
        val = val * 10;
      }

      delay(val);
      lc1.setLed(deviceNb, row, col, false);
      lc2.setLed(deviceNb, row, col, false);
    }
  }
}