#define ARDUINO 1000

#include <arduino.h>
#include "Screen.h"
#include "Controls.h"

#define BTN1 2
#define BTN2 3
#define BTN3 4

Screen screen;
Controls controls(BTN1, BTN2, BTN3);

void handleBtn1();
void handleBtn2();
void handleBtn3();

void setup()
{
    Serial.begin(9600);
    Serial.println("Debugging controls ...");
    Serial.flush();

    controls.setHandleBtn1(handleBtn1);
    controls.setHandleBtn2(handleBtn2);
    controls.setHandleBtn3(handleBtn3);
}

void loop()
{
    controls.loop();
}

void handleBtn1()
{
    Serial.println("Button 1 pressed");
}

void handleBtn2()
{
    Serial.println("Button 2 pressed");
}

void handleBtn3()
{
    Serial.println("Button 3 pressed");
}
