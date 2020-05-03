#include "Gui.h"
#include <arduino.h>

#define CURSOR_BLINK_RATE 200
#define REPAINT_RATE 10

Gui::Gui(State &state) : _state(state), _screen(Screen()), _splash(Splash(_screen))
{
    redraw(true);
    _splash.play(_mode, *this);
}

void Gui::loop()
{
    unsigned long now = millis();

    if ((now - _lastBlink) >= CURSOR_BLINK_RATE)
    {
        _lastBlink = now;   
        _cursorBlinkState = !_cursorBlinkState;
    }

    if ((now - _lastRepaint) >= REPAINT_RATE)
    {
        if (_splash.isPlaying())
        {
            _splash.loop();
        }
        else
        {
            _screen.setPixel(_cursorX, _cursorY, _cursorBlinkState);
        }

        _lastRepaint = now;
        _screen.repaint();
    }
}

void Gui::renderStep(uint8_t step)
{
    // chord cursor
    _screen.setPixel((step / 4) % 32, 4, true);
    _screen.setPixel(((step / 4) + 31) % 32, 4, false);

    // notes cursor
    _screen.setPixel(step % 32, 15, true);
    _screen.setPixel((step + 31) % 32, 15, false);
}

void Gui::redrawChords()
{
    // iterate over 8 bars (chords sequence loop)
    for (uint8_t step = 0; step < 128; step += 4)
    {
        // draw chord selections (only one channel for now)
        for (uint8_t selectionId = 0; selectionId < 4; selectionId++)
        {
            _screen.setPixel(step / 4, (3 - selectionId), _state.isChordSelected(step, 0, selectionId));
        }
    }
}

void Gui::redrawChannel(uint8_t channel)
{
    uint8_t vShift = channel == 0 ? 5 : 10;

    // iterate over 2 bars (notes sequence loop)
    for (uint8_t step = 0; step < 32; step++)
    {
        // draw note selections
        for (uint8_t selectionId = 0; selectionId < 4; selectionId++)
        {
            _screen.setPixel(step, (3 - selectionId) + vShift, _state.isNoteSelected(step, channel, selectionId));
        }

        // draw note trigs
        _screen.setPixel(step, vShift + 4, (_state.hasTrigOn(step, channel) != 0));
    }
}

void Gui::redrawAtCursorY()
{
    switch (getStateDestination())
    {
    // chords
    case 0:
        redrawChords();
        break;

    // channel 1 note selections / trigs
    case 1:
    case 2:
        redrawChannel(0);
        break;

    // channel 2 note selections / trigs
    case 3:
    case 4:
        redrawChannel(1);
        break;
    }
}

void Gui::redraw(bool resetScreen)
{
    if(resetScreen) 
    {
        _screen.clear();
    }

    redrawChords();
    redrawChannel(0);
    redrawChannel(1);
}

void Gui::moveCursorX(uint8_t n)
{
    redrawAtCursorY();
    _cursorX = n;
    _state.setStepEditAtStep(_cursorX);
}

void Gui::moveCursorY(uint8_t n)
{
    _cursorY = 15 - n;
    redrawAtCursorY();
}

void Gui::clickCursor()
{
    uint8_t selectionId;
    bool current;

    switch (getStateDestination())
    {
    // chords (assuming cursorY is 0-3)
    case 0:
        _state.setChordSelected(_cursorX * 4, (3 - _cursorY));
        break;

    //channel 1 notes (assuming cursorY is 5-8)
    case 1:
        selectionId = 3 - (_cursorY - 5);
        current = _state.isNoteSelected(_cursorX, 0, selectionId);
        _state.setNoteSelected(_cursorX, 0, selectionId, !current);
        break;

    // channel 1 trigs
    case 2:
        current = _state.hasTrigOn(_cursorX, 0);
        _state.setTrig(_cursorX, 0, !current);
        break;

    // channel 2 notes (assuming cursorY is 10-13)
    case 3:
        selectionId = 3 - (_cursorY - 10);
        current = _state.isNoteSelected(_cursorX, 1, selectionId);
        _state.setNoteSelected(_cursorX, 1, selectionId, !current);
        break;

    // channel 2 trigs
    case 4:
        current = _state.hasTrigOn(_cursorX, 1);
        _state.setTrig(_cursorX, 1, !current);
        break;
    }
}

void Gui::switchMode(uint8_t mode)
{
    _mode = mode;
    _splash.play(mode, *this);
}

// callback invoked at end of splash screen animation
void Gui::onSplashEnd()
{
    redraw(false);
}

void Gui::nudge(uint8_t amount, bool horizontal)
{
    switch (getStateDestination())
    {
    // chords
    case 0:
        _state.setChordNudge(amount, horizontal);
        break;

    // channel 1 notes
    case 1:
        _state.setNotesNudge(0, amount, horizontal);
        break;

    // channel 1 trigs
    case 2:
        if (horizontal)
        {
            _state.setTrigNudge(0, amount);
        }
        break;

    // channel 2 notes
    case 3:
        _state.setNotesNudge(1, amount, horizontal);
        break;

    // channel 2 trigs
    case 4:
        if (horizontal)
        {
            _state.setTrigNudge(1, amount);
        }
        break;
    }

    redrawAtCursorY();
}

void Gui::handleChordIn(uint8_t *chord, uint8_t nbNotes)
{
    _state.handleChord(chord, nbNotes, getStateDestination());
    redrawAtCursorY();
}

void Gui::loopSteps()
{
    _state.loopSteps(getStateDestination());
    redrawAtCursorY();
}

uint8_t Gui::getStateDestination()
{
    switch (_cursorY)
    {
    // 0-3 -> chords
    case 0:
    case 1:
    case 2:
    case 3:
        return 0;

    // 5-8 -> channel 1 note selections
    case 5:
    case 6:
    case 7:
    case 8:
        return 1;

    // 9 -> channel 1 trigs
    case 9:
        return 2;

    // 10-13 -> channel 2 note selections
    case 10:
    case 11:
    case 12:
    case 13:
        return 3;

    // 14 -> channel 2 trigs
    case 14:
        return 4;

    // unmapped
    default:
        return 42;
    }
}