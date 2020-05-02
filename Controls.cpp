#include "Controls.h"

#define CONTROLS_READ_FREQ 10

Controls::Controls()
    : btn1(PushButton(PIN2))
    , btn2(PushButton(PIN3))
    , btn3(PushButton(PIN4))
    , pot1(Potentiometer(A2))
    , pot2(Potentiometer(A3))
    , pot3(Potentiometer(A4))
    , pot4(Potentiometer(A5)) { }

void Controls::loop()
{
    unsigned long time = millis();
    if (time - _lastPeek > 10)
    {
        btn1.peek();
        btn2.peek();
        btn3.peek();
        pot1.peek();
        pot2.peek();
        pot3.peek();
        pot4.peek();

        _lastPeek = time;
    }
}