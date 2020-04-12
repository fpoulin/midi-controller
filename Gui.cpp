#include <LedControl.h>
#include <arduino.h>
#include "Gui.h"

#define CURSOR_BLINK_RATE 200
#define REPAINT_RATE 10

Gui::Gui(State &state) : _state(state), _screen(Screen())
{
    this->reset();
}

void Gui::loop()
{
    unsigned long now = millis();

    if((now - this->_lastBlink) >= CURSOR_BLINK_RATE) {
        this->_lastBlink = now;
        this->_cursorBlinkState = !this->_cursorBlinkState;
    }

    if ((now - this->_lastRepaint) >= REPAINT_RATE)
    {
        this->_lastRepaint = now;
        this->_screen.setPixel(this->_cursorX, this->_cursorY, this->_cursorBlinkState);
        this->_screen.repaint();
    }
}

void Gui::renderStep(uint8_t step)
{
    // chord cursor
    this->_screen.setPixel((step / 4) % 32, 4, true);
    this->_screen.setPixel(((step / 4) + 31) % 32, 4, false);

    // notes cursor
    this->_screen.setPixel(step % 32, 15, true);
    this->_screen.setPixel((step + 31) % 32, 15, false);
}

void Gui::moveCursorX(uint8_t n)
{
    this->redrawAt(this->_cursorY);
    this->_cursorX = n;
}

void Gui::moveCursorY(uint8_t n)
{
    this->redrawAt(this->_cursorY);
    this->_cursorY = n;
}

void Gui::clickCursor(bool toggle)
{
    switch ((int)this->_cursorY)
    {
    // 0-3 -> chords
    case 0:
    case 1:
    case 2:
    case 3:
        if (toggle)
        {
            this->_state.setChordSelected(this->_cursorX * 4, (3 - this->_cursorY));
        }
        break;

    // 5-8 -> channel 1 note selections
    case 5:
    case 6:
    case 7:
    case 8:
        this->_state.setNoteSelected(this->_cursorX, 0, (3 - (this->_cursorY - 5)), toggle);
        break;

    // 9 -> channel 1 trigs
    case 9:
        this->_state.setTrig(this->_cursorX, 0, toggle);
        break;

    // 10-13 -> channel 2 note selections
    case 10:
    case 11:
    case 12:
    case 13:
        this->_state.setNoteSelected(this->_cursorX, 1, (3 - (this->_cursorY - 10)), toggle);
        break;

    // 14 -> channel 2 trigs
    case 14:
        this->_state.setTrig(this->_cursorX, 1, toggle);
        break;
    }
}

void Gui::redrawAt(uint8_t y)
{
    if (y < 5)
    {
        this->redrawChords();
    }
    else if (y < 10)
    {
        this->redrawChannel(0);
    }
    else
    {
        this->redrawChannel(1);
    }
}

void Gui::redrawChords()
{
    // iterate over 8 bars (chords sequence loop)
    for (uint8_t step = 0; step < 128; step += 4)
    {
        // draw chord selections (only one channel for now)
        for (uint8_t selectionId = 0; selectionId < 4; selectionId++)
        {
            this->_screen.setPixel(step / 4, (3 - selectionId), this->_state.isChordSelected(step, 0, selectionId));
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
            this->_screen.setPixel(step, (3 - selectionId) + vShift, this->_state.isNoteSelected(step, channel, selectionId));
        }

        // draw note trigs
        this->_screen.setPixel(step, vShift + 4, (this->_state.hasTrigOn(step, channel) != 0));
    }
}

void Gui::reset()
{
    this->_screen.clear();

    this->redrawChords();
    this->redrawChannel(0);
    this->redrawChannel(1);
}