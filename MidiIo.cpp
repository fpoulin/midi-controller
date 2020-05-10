#include <MIDI.h>
#include "MidiIo.h"

#define NB_CHANNELS_OUT 2
#define MAX_CHORD_NOTES 4
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
uint8_t _channelIn = MIDI_CHANNEL_IN;
uint8_t _channelOut[NB_CHANNELS_OUT] = {1};
uint8_t _lastNotes[NB_CHANNELS_OUT][MAX_CHORD_NOTES] = {{0}};

uint8_t _nbKeyPressed = 0;
uint8_t _nbNotesToSend = 0;
uint8_t _chord[MAX_CHORD_NOTES];
boolean _yieldChord = false;
uint8_t _yieldAtMinimum = 0;

void (*_onStep)(uint8_t step, void (*sendNote)(uint8_t channel, uint8_t *notes));
void (*_onChord)(uint8_t *chord, uint8_t nbNotes);
void (*_onStop)(void);

void init(
    void (*onStep)(uint8_t step, void (*sendNote)(uint8_t channel, uint8_t *notes)),
    void (*onChord)(uint8_t *chord, uint8_t nbNotes),
    void (*onStop)(void))
{
    _onStep = onStep;
    _onChord = onChord;
    _onStop = onStop;

    for (uint8_t i = 0; i < NB_CHANNELS_OUT; i++)
    {
        _channelOut[i] = i + 1;
    }

    reset();

    MIDI.begin(_channelIn);
    MIDI.turnThruOff();
    MIDI.setHandleClock(handleClock);
    MIDI.setHandleStart(handleStart);
    MIDI.setHandleStop(handleStop);
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
}

void sendNotes(uint8_t channelIdx, uint8_t *notes)
{
    for (uint8_t i = 0; i < MAX_CHORD_NOTES; i++)
    {
        if (_lastNotes[channelIdx][i] != 0)
        {
            MIDI.sendNoteOn(_lastNotes[channelIdx][i], 0, _channelOut[channelIdx]);
        }

        _lastNotes[channelIdx][i] = notes[i];
        if (notes[i] != 0)
        {
            MIDI.sendNoteOn(notes[i], 127, _channelOut[channelIdx]);
        }
    }
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

    for (uint8_t channelIdx = 0; channelIdx < NB_CHANNELS_OUT; channelIdx++)
    {
        for (uint8_t i = 0; i < MAX_CHORD_NOTES; i++)
        {
            if (_lastNotes[channelIdx][i] != 0)
            {
                MIDI.sendNoteOn(_lastNotes[channelIdx][i], 0, _channelOut[channelIdx]);
            }
        }
    }

    reset();
}

void handleNoteOn(byte channel, byte note, byte velocity)
{
    if (_yieldAtMinimum == 0)
        return;

    if (_nbKeyPressed < MAX_CHORD_NOTES)
    {
        _chord[_nbKeyPressed++] = note;
        _nbNotesToSend = max(_nbNotesToSend, _nbKeyPressed);
        if (_nbKeyPressed >= _yieldAtMinimum)
        {
            _yieldChord = true;
        }
    }
}

void handleNoteOff(byte channel, byte note, byte velocity)
{
    if (_yieldAtMinimum == 0)
        return;

    if (!--_nbKeyPressed && _yieldChord)
    {
        _yieldChord = false;
        _onChord(_chord, _nbNotesToSend);
        _nbNotesToSend = 0;
    }
}

void loop()
{
    MIDI.read();
}

void setChordYieldMinimum(uint8_t yieldSize)
{
    _yieldAtMinimum = min(yieldSize, MAX_CHORD_NOTES);
}

void setMidiChannelIn(uint8_t channel)
{
    _channelIn = channel;
    MIDI.setInputChannel(_channelIn);
}

void setMidiChannelOut(uint8_t channelIdx, uint8_t channel)
{
    for (uint8_t i = 0; i < MAX_CHORD_NOTES; i++)
    {
        if (_lastNotes[channelIdx][i] != 0)
        {
            MIDI.sendNoteOn(_lastNotes[channelIdx][i], 0, _channelOut[channelIdx]);
        }
    }
    _channelOut[channelIdx] = channel;
}

uint8_t getMidiChannelIn()
{
    return _channelIn;
}

uint8_t getMidiChannelOut(uint8_t channelIdx)
{
    return _channelOut[channelIdx];
}

void reset()
{
    _playing = false;
    _clock = 0;
    _step = 0;
    _nbKeyPressed = 0;
    _yieldChord = false;

    for (uint8_t i = 0; i < MAX_CHORD_NOTES; i++)
    {
        for (uint8_t channel = 0; channel < NB_CHANNELS_OUT; channel++)
        {
            _lastNotes[channel][i] = 0;
        }

        _chord[i] = 0;
    }
}

END_MIDI_IO_NAMESPACE