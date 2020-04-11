#define ARDUINO 1000

#include <arduino.h>
#include "Screen.h"
#include "Controls.h"
#include "PushButton.h"
#include "Potentiometer.h"

Screen screen;
Controls controls(
    PushButton(PIN2),
    PushButton(PIN3),
    PushButton(PIN4),
    Potentiometer(A2),
    Potentiometer(A3),
    Potentiometer(A4),
    Potentiometer(A5));

void handleBtn1();
void handleBtn2();
void handleBtn3();
void handlePot1(uint8_t oldValue, uint8_t newValue);
void handlePot2(uint8_t oldValue, uint8_t newValue);
void handlePot3(uint8_t oldValue, uint8_t newValue);
void handlePot4(uint8_t oldValue, uint8_t newValue);

uint8_t cursorX = 0;
uint8_t cursorY = 0;

void setup()
{
    Serial.begin(9600);
    Serial.println("Debugging controls ...");
    Serial.flush();

    controls.setHandleBtn1(handleBtn1);
    controls.setHandleBtn2(handleBtn2);
    controls.setHandleBtn3(handleBtn3);
    controls.setHandlePot1(handlePot1, 0, 15);
    controls.setHandlePot2(handlePot2, 0, 31);
    controls.setHandlePot3(handlePot3, 0, 1);
    controls.setHandlePot4(handlePot4, 0, 127);
}

void loop()
{
    controls.loop();
}

void handleBtn1()
{
    Serial.println("Button 1 pressed (randomize screen)");

    randomSeed(millis());
    for (uint8_t i = 0; i < 32; i++)
    {
        for (uint8_t j = 0; j < 16; j++)
        {
            screen.setPixel(i, j, random(100) > 30);
        }
    }
    screen.repaint();
}

void handleBtn2()
{
    Serial.println("Button 2 pressed (set pot 4 to another handler with another range)");
    controls.setHandlePot4(otherHandler, 1, 8);
}

void handleBtn3()
{
    Serial.println("Button 3 pressed (restore pot 4 defaults)");
    controls.setHandlePot4(handlePot4, 0, 127);
}

void handlePot1(uint8_t oldValue, uint8_t newValue)
{
    Serial.print("Pot 1 set to ");
    Serial.println(newValue);

    screen.setPixel(cursorX, oldValue, false);
    screen.setPixel(cursorX, newValue, true);
    screen.repaint();

    cursorY = newValue;
}

void handlePot2(uint8_t oldValue, uint8_t newValue)
{
    Serial.print("Pot 2 set to ");
    Serial.println(newValue);

    screen.setPixel(oldValue, cursorY, false);
    screen.setPixel(newValue, cursorY, true);
    screen.repaint();

    cursorX = newValue;
}

void handlePot3(uint8_t oldValue, uint8_t newValue)
{
    Serial.print("Pot 3 set to ");
    Serial.println(newValue);
}

void handlePot4(uint8_t oldValue, uint8_t newValue)
{
    Serial.print("Pot 4 set to ");
    Serial.println(newValue);
}

void otherHandler(uint8_t oldValue, uint8_t newValue)
{
    Serial.print("This is another handler ");
    Serial.println(newValue);
}