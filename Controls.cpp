#include "Controls.h"

#define CONTROLS_READ_FREQ 10

Controls::Controls(PushButton btn1, PushButton btn2, PushButton btn3, Potentiometer pot1, Potentiometer pot2, Potentiometer pot3, Potentiometer pot4)
    : _btn1(btn1), _btn2(btn2), _btn3(btn3), _pot1(pot1), _pot2(pot2), _pot3(pot3), _pot4(pot4) {}

void Controls::loop()
{
    unsigned long time = millis();
    if (time - this->_lastPeek > 10)
    {
        this->_btn1.peek();
        this->_btn2.peek();
        this->_btn3.peek();
        this->_pot1.peek();
        this->_pot2.peek();
        this->_pot3.peek();
        this->_pot4.peek();

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

void Controls::setHandlePot1(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max)
{
    this->_pot1.setCallback(onChange, min, max);
}

void Controls::setHandlePot2(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max)
{
    this->_pot2.setCallback(onChange, min, max);
}

void Controls::setHandlePot3(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max)
{
    this->_pot3.setCallback(onChange, min, max);
}

void Controls::setHandlePot4(void (*onChange)(uint8_t oldValue, uint8_t newValue), uint8_t min, uint8_t max)
{
    this->_pot4.setCallback(onChange, min, max);
}