#pragma once

class SyncPulse
{
private:
    bool _isPulsing;
    unsigned long _lastPulseAt;
public:
    void setup();
    void sendPulse();
    void loop();
    void reset();
};