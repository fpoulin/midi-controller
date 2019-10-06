#pragma once

#define MIDI_IO_NAMESPACE midiIo
#define BEGIN_MIDI_IO_NAMESPACE \
    namespace MIDI_IO_NAMESPACE \
    {
#define END_MIDI_IO_NAMESPACE }

BEGIN_MIDI_IO_NAMESPACE

void init(void (*onStep)(const int& step, void (*sendNote)(const byte& note)));
void loop();

END_MIDI_IO_NAMESPACE