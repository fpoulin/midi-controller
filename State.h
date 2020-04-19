#include <arduino.h>

#pragma once

#define STORAGE_VERSION 1 // to be increased when changing constants below
#define NB_CHORDS 4
#define NB_NOTES_PER_CHORD 4
#define NB_CHANNELS 2
#define NB_CHORD_BARS 8
#define NB_CHORDS_PER_BAR 4
#define NB_NOTES_BARS 2
#define NB_NOTES_PER_BAR 16

class State
{
private:
    uint8_t _currChordInputId; // 0-(NB_CHORDS-1)

    uint8_t _chords[NB_CHORDS][NB_NOTES_PER_CHORD];                   // NB_CHORDS chords of NOTES_PER_CHORD notes
    uint8_t _chordSel[NB_CHANNELS][NB_CHORD_BARS][NB_CHORDS_PER_BAR]; // selection of a chord: [channel][bar][beat*]
    uint8_t _notesSel[NB_CHANNELS][NB_NOTES_BARS][NB_NOTES_PER_BAR];  // selection of notes: [channel][bar][trig*]
    uint8_t _trigs[NB_CHANNELS][NB_NOTES_BARS][NB_NOTES_PER_BAR];     // triggers: [channel][bar][trig*]
    uint8_t _transpose[NB_CHANNELS];                                  // transpose octave: [channel] (shifted by -2)

    uint8_t _notesToPlay[NB_NOTES_PER_CHORD]; // buffer for notes to be played

    uint8_t getTrig(uint8_t step);
    uint8_t getBeat(uint8_t step);
    uint8_t getBar(uint8_t step);

    // KISS (and dirty)
    friend class Storage;

public:
    State();

    uint8_t hasTrigOn(uint8_t step, uint8_t channel);
    bool isChordSelected(uint8_t step, uint8_t channel, uint8_t chordSelectionId);
    bool isNoteSelected(uint8_t step, uint8_t channel, uint8_t noteSelectionId);
    uint8_t *getNotes(uint8_t step, uint8_t channel);

    void addChord(uint8_t *chord);
    void setTrig(uint8_t step, uint8_t channel, bool state);
    void setChordSelected(uint8_t step, uint8_t chordSelectionId);
    void setNoteSelected(uint8_t step, uint8_t channel, uint8_t noteSelectionId, bool state);
    void setTranspose(uint8_t channel, uint8_t octave);

    void reset(bool soft);
};