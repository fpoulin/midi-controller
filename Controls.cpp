#include "Controls.h"
#include "Mode.h"

#define CONTROLS_READ_FREQ 10

Controls::Controls(PushButton &btn1, PushButton &btn2, PushButton &btn3)
    : _btn1(btn1), _btn2(btn2), _btn3(btn3)
    , pot1(Potentiometer(A2))
    , pot2(Potentiometer(A3))
    , pot3(Potentiometer(A4))
    , pot4(Potentiometer(A5)) { }

void Controls::loop()
{
    unsigned long time = millis();
    if (time - _lastPeek > 10)
    {
        _btn1.peek();
        _btn2.peek();
        _btn3.peek();
        pot1.peek();
        pot2.peek();
        pot3.peek();
        pot4.peek();

        _lastPeek = time;
    }
}

void Controls::setHandleBtn1(void (*onClick)(void))
{
    _btn1.setCallback(onClick);
}

void Controls::setHandleBtn2(void (*onClick)(void))
{
    _btn2.setCallback(onClick);
}

void Controls::setHandleBtn3(void (*onClick)(void))
{
    _btn3.setCallback(onClick);
}