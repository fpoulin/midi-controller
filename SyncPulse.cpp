#include "SyncPulse.h"
#include <arduino.h>

#define PULSE_PIN_OUT 5
#define PULSE_MS 4

void SyncPulse::setup()
{
    pinMode(PULSE_PIN_OUT, OUTPUT);
    this->_isPulsing = false;
}

void SyncPulse::sendPulse()
{
    digitalWrite(PULSE_PIN_OUT, HIGH);
    this->_isPulsing = true;
    this->_lastPulseAt = millis();
}

void SyncPulse::loop()
{
    // check if we are pulsing and need to stop it
    if (this->_isPulsing && (millis() - this->_lastPulseAt) >= PULSE_MS)
    {
        digitalWrite(PULSE_PIN_OUT, LOW);
        this->_isPulsing = false;
    }
}

void SyncPulse::reset()
{
    digitalWrite(PULSE_PIN_OUT, LOW);
    this->_isPulsing = false;
}