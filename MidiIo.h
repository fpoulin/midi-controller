#pragma once

#define MIDI_IO_NAMESPACE midiIo
#define BEGIN_MIDI_IO_NAMESPACE \
    namespace MIDI_IO_NAMESPACE \
    {
#define END_MIDI_IO_NAMESPACE }

BEGIN_MIDI_IO_NAMESPACE

void init(
    void (*onStep)(uint8_t step, void (*sendNote)(uint8_t channel, uint8_t *notes)),
    void (*onNote)(uint8_t* chord, uint8_t nbNotes),
    void (*onStop)(void));

void loop();
void setChordYieldMinimum(uint8_t yieldSize);
void setMidiChannelIn(uint8_t channel);
void setMidiChannelOut(uint8_t channelIdx, uint8_t channel);
uint8_t getMidiChannelIn();
uint8_t getMidiChannelOut(uint8_t channelIdx);

END_MIDI_IO_NAMESPACE