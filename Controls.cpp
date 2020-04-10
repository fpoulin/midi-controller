#include "Controls.h"

Controls::Controls(uint8_t pinBtn1, uint8_t pinBtn2, uint8_t pinBtn3)
    : _btn1(pinBtn1), _btn2(pinBtn2), _btn3(pinBtn3)
{
    pinMode(A1, INPUT); // linear

    pinMode(A2, INPUT); // knob 4
    pinMode(A3, INPUT); // knob 3
    pinMode(A4, INPUT); // knob 2
    pinMode(A5, INPUT); // knob 1
}

void Controls::loop()
{
    _btn1.peek();
    _btn2.peek();
    _btn3.peek();
}

void Controls::setHandleBtn1(void (*onClick)(void))
{
    _btn1.setHandleBtn(onClick);
}

void Controls::setHandleBtn2(void (*onClick)(void))
{
    _btn2.setHandleBtn(onClick);
}

void Controls::setHandleBtn3(void (*onClick)(void))
{
    _btn3.setHandleBtn(onClick);
}

void Controls::setHandleKnob1(void (*onChange)(uint8_t oldValue, uint8_t newValue))
{
    this->_onChangeKnob1 = onChange;
}

void Controls::setHandleKnob2(void (*onChange)(uint8_t oldValue, uint8_t newValue))
{
    this->_onChangeKnob2 = onChange;
}

void Controls::setHandleKnob3(void (*onChange)(uint8_t oldValue, uint8_t newValue))
{
    this->_onChangeKnob3 = onChange;
}

void Controls::setHandleKnob4(void (*onChange)(uint8_t oldValue, uint8_t newValue))
{
    this->_onChangeKnob4 = onChange;
}

void Controls::setHandleLinear(void (*onChange)(uint8_t oldValue, uint8_t newValue))
{
    this->_onChangeLinear = onChange;
}