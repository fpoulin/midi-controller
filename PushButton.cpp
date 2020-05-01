#include "PushButton.h"
#include <arduino.h>

#define DEBOUNCE_TIME 500

PushButton::PushButton(uint8_t pin) : _pin(pin)
{
    pinMode(pin, INPUT_PULLUP);
}

void PushButton::peek()
{
    if (digitalRead(_pin) == LOW)
    {
        if (!_clicking)
        {
            unsigned long time = millis();
            if (time - _lastClick > DEBOUNCE_TIME)
            {
                _clicking = true;
                _lastClick = time;
                _onClick();
            }
        }
    }
    else
    {
        _clicking = false;
    }
}

void PushButton::setCallback(void (*onClick)(void))
{
    _onClick = onClick;
}