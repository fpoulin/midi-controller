#include <MIDI.h>
#include "MidiIo.h"

#define MIDI_CHANNEL_IN 1

BEGIN_MIDI_IO_NAMESPACE

void handleClock();
void handleStart();
void handleStop();
void handleNoteOn(byte channel, byte note, byte velocity);
void handleNoteOff(byte channel, byte note, byte velocity);
void reset();

midi::MidiInterface<HardwareSerial> MIDI((HardwareSerial &)Serial);

boolean _playing = false;
uint8_t _clock = 0;
uint8_t _step = 0;
uint8_t _lastNotes[2][4]; // [channel][note]

uint8_t _nbKeyPressed = 0;
uint8_t _chord[4];
boolean _sendChord = false;

void (*_onStep)(uint8_t step, void (*sendNote)(uint8_t channel, uint8_t *notes));
void (*_onChord)(uint8_t *chord);
void (*_onStop)(void);

void init(
    void (*onStep)(uint8_t step, void (*sendNote)(uint8_t channel, uint8_t *notes)),
    void (*onChord)(uint8_t *chord),
    void (*onStop)(void))
{
    _onStep = onStep;
    _onChord = onChord;
    _onStop = onStop;

    reset();

    MIDI.begin(MIDI_CHANNEL_IN);
    MIDI.turnThruOff();
    MIDI.setHandleClock(handleClock);
    MIDI.setHandleStart(handleStart);
    MIDI.setHandleStop(handleStop);
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
}

void sendNotes(uint8_t channel, uint8_t *notes)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        if (_lastNotes[channel][i] != 0)
        {
            MIDI.sendNoteOn(_lastNotes[channel][i], 0, channel + 1);
        }

        _lastNotes[channel][i] = notes[i];
        if (notes[i] != 0)
        {
            MIDI.sendNoteOn(notes[i], 127, channel + 1);
        }
    }
}

void loop()
{
    MIDI.read();
}

void handleClock()
{
    _clock = _clock % 6;
    if (_playing && _clock++ == 0)
    {
        _onStep(_step, sendNotes);
        _step++; // let it overflow (255 -> 0)
    }
}

void handleStart()
{
    _playing = true;
}

void handleStop()
{
    _onStop();

    for (uint8_t channel = 0; channel < 2; channel++)
    {
        for (uint8_t i = 0; i < 4; i++)
        {
            if (_lastNotes[channel][i] != 0)
            {
                MIDI.sendNoteOn(_lastNotes[channel][i], 0, channel+1);
            }
        }
    }

    reset();
}

void handleNoteOn(byte channel, byte note, byte velocity)
{
    if (_nbKeyPressed < 4)
    {
        _chord[_nbKeyPressed++] = note;
        if (_nbKeyPressed == 4)
        {
            _sendChord = true;
        }
    }
}

void handleNoteOff(byte channel, byte note, byte velocity)
{
    if (!--_nbKeyPressed && _sendChord)
    {
        _sendChord = false;
        _onChord(_chord);
    }
}

void reset()
{
    _playing = false;
    _clock = 0;
    _step = 0;
    _nbKeyPressed = 0;
    _sendChord = false;

    for (uint8_t i = 0; i < 4; i++)
    {
        _lastNotes[0][i] = 0;
        _lastNotes[1][i] = 0;
        _chord[i] = 0;
    }
}

END_MIDI_IO_NAMESPACE