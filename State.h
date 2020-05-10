#pragma once

#include <arduino.h>

#define STORAGE_STATE_VERSION 3 // to be increased when changing constants below
#define NB_CHORDS 4
#define NB_NOTES_PER_CHORD 4
#define NB_CHANNELS 2
#define NB_CHORD_BARS 8
#define NB_CHORDS_PER_BAR 4 // times NB_CHORD_BARS = 32 (or else, drama)
#define NB_NOTES_BARS 2
#define NB_NOTES_PER_BAR 16  // times NB_NOTES_BARS = 32 (or else, drama)

class State
{
private:
    uint8_t _chords[NB_CHORDS][NB_NOTES_PER_CHORD];                   // NB_CHORDS chords of NOTES_PER_CHORD notes
    uint8_t _chordSel[NB_CHORD_BARS][NB_CHORDS_PER_BAR];              // selection of a chord: [bar][beat*]
    uint8_t _notesSel[NB_CHANNELS][NB_NOTES_BARS][NB_NOTES_PER_BAR];  // selection of notes: [channel][bar][trig*]
    uint8_t _trigs[NB_CHANNELS][NB_NOTES_BARS][NB_NOTES_PER_BAR];     // triggers: [channel][bar][trig*]
    uint8_t _transpose[NB_CHANNELS];                                  // transpose octave: [channel] (shifted by -2)
    bool _mute[NB_CHANNELS] = {false};                                // mute channels

    uint8_t getTrig(uint8_t step);
    uint8_t getBeat(uint8_t step);
    uint8_t getBar(uint8_t step);

    // nudge stuff
    uint8_t _chordNudges[2] = {0};               // [horizontal/vertical]
    uint8_t _noteNudges[NB_CHANNELS][2] = {{0}}; // [channel][horizontal/vertical]
    uint8_t _trigNudges[NB_CHANNELS] = {0};      // [channel]
    uint8_t _nudgeBuffer[32];                    // buffer used when applying nudges

    // chords input stuff
    uint8_t _handleChordMode;  // 0: fa, 1:store chord, 2:set ref notes, 3: step edit
    uint8_t _currChordInputId; // 0-(NB_CHORDS-1)
    uint8_t _refNotes[NB_NOTES_PER_CHORD] = {0};
    uint8_t _stepEditAtStep;

    uint8_t _notesToPlay[NB_NOTES_PER_CHORD]; // buffer for notes to be played

    // KISS (and dirty)
    friend class Storage;

public:
    State();

    uint8_t hasTrigOn(uint8_t step, uint8_t channel);
    bool isChordSelected(uint8_t step, uint8_t channel, uint8_t chordSelectionId);
    bool isNoteSelected(uint8_t step, uint8_t channel, uint8_t noteSelectionId);
    uint8_t *getNotes(uint8_t step, uint8_t channel);

    void setTrig(uint8_t step, uint8_t channel, bool state);
    void setChordSelected(uint8_t step, uint8_t chordSelectionId);
    void setNoteSelected(uint8_t step, uint8_t channel, uint8_t noteSelectionId, bool state);
    void setTranspose(uint8_t channel, uint8_t octave);
    void toggleMuteChannel(uint8_t channel);

    void setChordNudge(uint8_t amount, bool horizontal);
    void setNotesNudge(uint8_t channel, uint8_t amount, bool horizontal);
    void setTrigNudge(uint8_t channel, uint8_t amount);
    void applyAllNudges();
    void resetAllNudges();

    void setHandleChordMode(uint8_t mode);
    void handleChord(uint8_t *chord, uint8_t nbNotes, uint8_t destination);
    void resetChordInputId();
    void setStepEditAtStep(uint8_t step); // [0-31]
    void loopSteps(uint8_t destination);

    void reset(bool soft);
};