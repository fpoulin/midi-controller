#include "Controls.h"

Controls::Controls(PushButton btn1, PushButton btn2, PushButton btn3, Potentiometer rot1, Potentiometer rot2, Potentiometer rot3, Potentiometer rot4, Potentiometer lin)
    : _btn1(btn1), _btn2(btn2), _btn3(btn3), _rot1(rot1), _rot2(rot2), _rot3(rot3), _rot4(rot4), _lin(lin) {}

void Controls::loop()
{
    unsigned long time = millis();
    if (time - this->_lastPeek > 100)
    {
        _btn1.peek();
        _btn2.peek();
        _btn3.peek();
        _rot1.peek();
        _rot2.peek();
        _rot3.peek();
        _rot4.peek();
        _lin.peek();

        this->_lastPeek = time;
    }
}

void Controls::setHandleBtn1(void (*onClick)(void))
{
    this->_btn1.setCallback(onClick);
}

void Controls::setHandleBtn2(void (*onClick)(void))
{
    this->_btn2.setCallback(onClick);
}

void Controls::setHandleBtn3(void (*onClick)(void))
{
    this->_btn3.setCallback(onClick);
}

void Controls::setHandleRotary1(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max)
{
    this->_rot1.setCallback(onChange, min, max);
}

void Controls::setHandleRotary2(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max)
{
    this->_rot2.setCallback(onChange, min, max);
}

void Controls::setHandleRotary3(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max)
{
    this->_rot3.setCallback(onChange, min, max);
}

void Controls::setHandleRotary4(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max)
{
    this->_rot4.setCallback(onChange, min, max);
}

void Controls::setHandleLinear1(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max)
{
    this->_lin.setCallback(onChange, min, max);
}