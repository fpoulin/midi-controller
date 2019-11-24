#include <MIDI.h>
#include "MidiIo.h"

BEGIN_MIDI_IO_NAMESPACE

void handleClock();
void handleStart();
void handleStop();
void handleNoteOn(byte channel, byte note, byte velocity);
void handleNoteOff(byte channel, byte note, byte velocity);
void reset();

midi::MidiInterface<HardwareSerial> MIDI((HardwareSerial &)Serial);

bool _playing = false;
unsigned long _ticks = 0;
int _step = 0;
uint8_t lastNotes[2][4]; // [channel][note]

uint8_t nbKeyPressed = 0;
uint8_t chord[4];
bool sendChord = false;

void (*_onStep)(int step, void (*sendNote)(uint8_t channel, uint8_t *notes));
void (*_onChord)(uint8_t *chord);
void (*_onStop)(void);

void init(
    void (*onStep)(int step, void (*sendNote)(uint8_t channel, uint8_t *notes)),
    void (*onChord)(uint8_t *chord),
    void (*onStop)(void))
{
    _onStep = onStep;
    _onChord = onChord;
    _onStop = onStop;

    reset();

    MIDI.begin(MIDI_CHANNEL_OMNI);
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
        if (lastNotes[channel][i] != 0)
        {
            MIDI.sendNoteOn(lastNotes[channel][i], 0, channel + 1);
        }

        lastNotes[channel][i] = notes[i];
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
    if (_playing && _ticks++ % 6 == 0)
    {
        _onStep(_step, sendNotes);
        _step++;
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
            if (lastNotes[channel][i] != 0)
            {
                MIDI.sendNoteOn(lastNotes[channel][i], 0, channel+1);
            }
        }
    }

    reset();
}

void handleNoteOn(byte channel, byte note, byte velocity)
{
    if (nbKeyPressed < 4)
    {
        chord[nbKeyPressed++] = note;
        if (nbKeyPressed == 4)
        {
            sendChord = true;
        }
    }
}

void handleNoteOff(byte channel, byte note, byte velocity)
{
    if (!--nbKeyPressed && sendChord)
    {
        _onChord(chord);
    }
}

void reset()
{
    _playing = false;
    _ticks = 0;
    _step = 0;
    nbKeyPressed = 0;
    sendChord = false;

    for (uint8_t i = 0; i < 4; i++)
    {
        lastNotes[0][i] = 0;
        lastNotes[1][i] = 0;
        chord[i] = 0;
    }
}

END_MIDI_IO_NAMESPACE