#define ARDUINO 1000

#include <arduino.h>
#include "Screen.h"
#include "Controls.h"
#include "PushButton.h"
#include "Potentiometer.h"

Screen screen;
Controls controls(
    PushButton(2),
    PushButton(3),
    PushButton(4),
    Potentiometer(A5, 1, 1024),
    Potentiometer(A4, 1, 1024),
    Potentiometer(A3, 1, 1024),
    Potentiometer(A2, 1, 1024),
    Potentiometer(A1, 1, 1024));

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
    controls.setHandleRotary1(handleRotary1, 1, 1024);
    controls.setHandleRotary2(handleRotary2, 1, 1024);
    controls.setHandleRotary3(handleRotary3, 1, 1024);
    controls.setHandleRotary4(handleRotary4, 1, 1024);
    controls.setHandleLinear1(handleLinear1, 1, 1024);
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

void handleRotary1(uint8_t oldValue, uint8_t newValue)
{
    Serial.print("Rotary 1 set to ");
    Serial.println(newValue);
    Serial.flush();
}

void handleRotary2(uint8_t oldValue, uint8_t newValue)
{
    Serial.print("Rotary 2 set to ");
    Serial.println(newValue);
}

void handleRotary3(uint8_t oldValue, uint8_t newValue)
{
    Serial.print("Rotary 3 set to ");
    Serial.println(newValue);
}

void handleRotary4(uint8_t oldValue, uint8_t newValue)
{
    Serial.print("Rotary 4 set to ");
    Serial.println(newValue);
}

void handleLinear1(uint8_t oldValue, uint8_t newValue)
{
    Serial.print("Linear 1 set to ");
    Serial.println(newValue);
}