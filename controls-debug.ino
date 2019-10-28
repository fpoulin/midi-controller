#define ARDUINO 1000

#include "Screen.h"
#include "Controls.h"

Screen screen;
Controls controls;

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
