#define ARDUINO 1000
#include "Gui.h"
#include "MidiIo.h"
#include "State.h"
#include "SyncPulse.h"
#include "Controls.h"
#include "PushButton.h"
#include "Potentiometer.h"

State _state;
Gui _gui(_state);
SyncPulse _syncPulse;
Controls _controls(
    PushButton(PIN2),
    PushButton(PIN3),
    PushButton(PIN4),
    Potentiometer(A2),
    Potentiometer(A3),
    Potentiometer(A4),
    Potentiometer(A5));

void playStep(uint8_t step, void (*sendNote)(uint8_t channel, uint8_t *notes));
void addChord(uint8_t *chord);
void stop();
void handleBtn1();
void handleBtn2();
void handleBtn3();
void handlePot1(uint8_t oldValue, uint8_t newValue);
void handlePot2(uint8_t oldValue, uint8_t newValue);
void handlePot3(uint8_t oldValue, uint8_t newValue);
void handlePot4(uint8_t oldValue, uint8_t newValue);

void setup()
{
    midiIo::init(playStep, addChord, stop);
    _syncPulse.setup();

    _controls.setHandleBtn1(handleBtn1);
    _controls.setHandleBtn2(handleBtn2);
    _controls.setHandleBtn3(handleBtn3);
    _controls.setHandlePot1(handlePot1, 0, 15); // move y
    _controls.setHandlePot2(handlePot2, 0, 31); // move x
    _controls.setHandlePot3(handlePot3, -2, 2);
    _controls.setHandlePot4(handlePot4, -2, 2);
}

void loop()
{
    midiIo::loop();
    _syncPulse.loop();
    _controls.loop();
}

void playStep(uint8_t step, void (*sendNote)(uint8_t channel, uint8_t *notes))
{
    if (step % 2 == 0)
    {
        _syncPulse.sendPulse();
    }
    
    _state.moveToStep(step);
    _gui.renderStep(step);

    for (uint8_t channel = 0; channel < 2; channel++)
    {
        if (_state.hasTrigOn(channel) != 0)
        {
            sendNote(channel, _state.getNotes(channel));
        }
    }
}

void addChord(uint8_t *chord)
{
    _state.addChord(chord);
}

void stop()
{
    _state.reset();
    _gui.reset();
    _syncPulse.reset();
}

void handleBtn1()
{
    _gui.clickCursor(true);
}

void handleBtn2()
{
    _gui.clickCursor(false);
}

void handleBtn3()
{
    _state.reset();
    _gui.reset();
}

void handlePot1(uint8_t oldValue, uint8_t newValue)
{
    _gui.moveCursorY(newValue);
}

void handlePot2(uint8_t oldValue, uint8_t newValue)
{
    _gui.moveCursorX(newValue);
}

void handlePot3(uint8_t oldValue, uint8_t newValue)
{
    // do nothing for now (later: control transpose channel 1)
}

void handlePot4(uint8_t oldValue, uint8_t newValue)
{
    // do nothing for now  (later: control transpose channel 2)
}