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
PushButton _btn1(PIN2);
PushButton _btn2(PIN3);
PushButton _btn3(PIN4);
Potentiometer _pot1(A2);
Potentiometer _pot2(A3);
Potentiometer _pot3(A4);
Potentiometer _pot4(A5);
Controls _controls(_btn1, _btn2, _btn3, _pot1, _pot2, _pot3, _pot4);

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
    _controls.setHandlePot3(handlePot3, 0, 4);
    _controls.setHandlePot4(handlePot4, 0, 4);
}

void loop()
{
    midiIo::loop();
    _syncPulse.loop();
    _controls.loop();
    _gui.loop();
}

void playStep(uint8_t step, void (*sendNote)(uint8_t channel, uint8_t *notes))
{
    if (step % 2 == 0)
    {
        _syncPulse.sendPulse();
    }

    for (uint8_t channel = 0; channel < 2; channel++)
    {
        if (_state.hasTrigOn(step, channel) != 0)
        {
            sendNote(channel, _state.getNotes(step, channel));
        }
    }

    _gui.renderStep(step);
}

void addChord(uint8_t *chord)
{
    _state.addChord(chord);
}

void stop()
{
    _state.reset(true);
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
    _state.reset(true);
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
    _state.setTranspose(0, newValue);
}

void handlePot4(uint8_t oldValue, uint8_t newValue)
{
    _state.setTranspose(1, newValue);
}