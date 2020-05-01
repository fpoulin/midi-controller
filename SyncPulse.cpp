#include "SyncPulse.h"
#include <arduino.h>

#define PULSE_PIN_OUT 5
#define PULSE_MS 4

void SyncPulse::setup()
{
    pinMode(PULSE_PIN_OUT, OUTPUT);
    _isPulsing = false;
}

void SyncPulse::sendPulse()
{
    digitalWrite(PULSE_PIN_OUT, HIGH);
    _isPulsing = true;
    _lastPulseAt = millis();
}

void SyncPulse::loop()
{
    // check if we are pulsing and need to stop it
    if (_isPulsing && (millis() - _lastPulseAt) >= PULSE_MS)
    {
        digitalWrite(PULSE_PIN_OUT, LOW);
        _isPulsing = false;
    }
}

void SyncPulse::reset()
{
    digitalWrite(PULSE_PIN_OUT, LOW);
    _isPulsing = false;
}