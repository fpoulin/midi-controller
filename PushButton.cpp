#include "PushButton.h"
#include <arduino.h>

#define DEBOUNCE_TIME 500

PushButton::PushButton(uint8_t pin) : _pin(pin)
{
    pinMode(pin, INPUT_PULLUP);
}

void PushButton::peek()
{
    if (digitalRead(this->_pin) == LOW)
    {
        if (!this->_clicking)
        {
            unsigned long time = millis();
            if (time - this->_lastClick > DEBOUNCE_TIME)
            {
                this->_clicking = true;
                this->_lastClick = time;
                this->_onClick();
            }
        }
    }
    else
    {
        this->_clicking = false;
    }
}

void PushButton::setHandleBtn(void (*onClick)(void))
{
    this->_onClick = onClick;
}