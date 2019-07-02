#define ARDUINO 1000
#include <LedControl.h>

LedControl lc1 = LedControl(2, 4, 3, 4);
LedControl lc2 = LedControl(5, 7, 6, 4);
unsigned long delaytime = 10;

// the setup function runs once when you press reset or power the board
void setup()
{
  for (int address = 0; address < lc1.getDeviceCount(); address++) {
    lc1.shutdown(address, false);
    lc1.setIntensity(address, 8);
    lc1.clearDisplay(address);
  }

  for (int address = 0; address < lc2.getDeviceCount(); address++) {
    lc2.shutdown(address, false);
    lc2.setIntensity(address, 8);
    lc2.clearDisplay(address);
  }
}

// the loop function runs over and over again forever
void loop()
{
  //read the number cascaded devices
  int devices = lc1.getDeviceCount();

  int count = 0;
  for (int i = 0; i < devices; i++)
  {
    int deviceNb = i;
    for (int j = 0; j < 8; j++)
    {
      int col = 7-j;
      double radFactor = 3.1415926535 / 180;
      int row = floor((sin(radFactor * (i * 8 + 7-col) / 32.0 * 360) + 1) / 2 * 7.99);

      lc1.setLed(deviceNb, row, col, true);
      lc2.setLed(deviceNb, row, col, true);
      delay(delaytime);
      lc1.setLed(deviceNb, row, col, false);
      lc2.setLed(deviceNb, row, col, false);
    }
  }
}