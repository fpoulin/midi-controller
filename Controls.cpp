#include "Controls.h"

#define BTN1 2
#define BTN2 3
#define BTN3 4

Controls::Controls()
{
    pinMode(A1, INPUT); // linear

    pinMode(A2, INPUT); // knob 4
    pinMode(A3, INPUT); // knob 3
    pinMode(A4, INPUT); // knob 2
    pinMode(A5, INPUT); // knob 1

    pinMode(BTN1, INPUT_PULLUP); // push 1
    pinMode(BTN2, INPUT_PULLUP); // push 2
    pinMode(BTN3, INPUT_PULLUP); // push 3
}

void Controls::loop()
{
    unsigned long time = millis();
    bool debounced = time - this->_debounce > 1000;

    if (digitalRead(BTN1) == LOW)
    {
        if (!this->_btn1Pressed && debounced)
        {
            this->_debounce = time;
            
            
            this->_onClickBtn1();
        }
    }
    else
    {
        this->_btn1Pressed = false;
    }

    if (digitalRead(BTN2) == LOW)
    {
        this->_onClickBtn2();
    }

    if (digitalRead(BTN3) == LOW)
    {
        this->_onClickBtn3();
    }
}

void Controls::setHandleBtn1(void (*onClick)(void))
{
    this->_onClickBtn1 = onClick;
}

void Controls::setHandleBtn2(void (*onClick)(void))
{
    this->_onClickBtn2 = onClick;
}

void Controls::setHandleBtn3(void (*onClick)(void))
{
    this->_onClickBtn3 = onClick;
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