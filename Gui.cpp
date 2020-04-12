#include <LedControl.h>
#include "Gui.h"

Gui::Gui(State &state) : _state(state), _screen(Screen())
{
    this->reset();
}

void Gui::renderStep(uint8_t step)
{
    // chord cursor
    this->_screen.setPixel((step / 4) % 32, 4, true);
    this->_screen.setPixel(((step / 4) + 31) % 32, 4, false);

    // notes cursor
    this->_screen.setPixel(step % 32, 15, true);
    this->_screen.setPixel((step + 31) % 32, 15, false);

    this->_screen.repaint();
}

void Gui::moveCursorX(uint8_t n)
{
    this->_cursorX = n;
}

void Gui::moveCursorY(uint8_t n)
{
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
        this->_state.setNoteSelected(this->_cursorX, 0, (3 - this->_cursorY - 5), toggle);
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
        this->_state.setNoteSelected(this->_cursorX, 1, (3 - this->_cursorY - 10), toggle);
        break;

    // 14 -> channel 2 trigs
    case 14:
        this->_state.setTrig(this->_cursorX, 1, toggle);
        break;
    }

    // apply on screen (faster than re-rendering the whole thing)
    this->reset(); // ############## for test
}

void Gui::reset()
{
    this->_screen.clear();

    // iterate over 8 bars (chords sequence loop)
    for (uint8_t step = 0; step < 128; step += 4)
    {
        // draw chord selections (only one channel for now)
        for (uint8_t selectionId = 0; selectionId < 4; selectionId++)
        {
            this->_screen.setPixel(step / 4, (3 - selectionId), this->_state.isChordSelected(step, 0, selectionId));
        }
    }

    // iterate over 2 bars (notes sequence loop)
    for (uint8_t step = 0; step < 32; step++)
    {
        // draw note selections
        for (uint8_t selectionId = 0; selectionId < 4; selectionId++)
        {
            this->_screen.setPixel(step, (3 - selectionId) + 5, this->_state.isNoteSelected(step, 0, selectionId));
            this->_screen.setPixel(step, (3 - selectionId) + 10, this->_state.isNoteSelected(step, 1, selectionId));
        }

        // draw note trigs
        this->_screen.setPixel(step, 9, (this->_state.hasTrigOn(step, 0) != 0));
        this->_screen.setPixel(step, 14, (this->_state.hasTrigOn(step, 1) != 0));
    }

    this->_screen.repaint();
}