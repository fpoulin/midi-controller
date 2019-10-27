#pragma once

#define MIDI_IO_NAMESPACE midiIo
#define BEGIN_MIDI_IO_NAMESPACE \
    namespace MIDI_IO_NAMESPACE \
    {
#define END_MIDI_IO_NAMESPACE }

BEGIN_MIDI_IO_NAMESPACE

void init(
    void (*onStep)(int step, void (*sendNote)(byte note)),
    void (*onNote)(byte note),
    void (*onStop)(void));

void loop();

END_MIDI_IO_NAMESPACE