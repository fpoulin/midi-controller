#include <LedControl.h>
#include "Gui.h"

Gui::Gui(State &state) : _state(state), _screen(Screen())
{
    this->reset();
}

void Gui::moveToStep(uint8_t step)
{
    // chord cursor
    this->_screen.setPixel((step / 4) % 32, 4, true);
    this->_screen.setPixel(((step / 4) + 31) % 32, 4, false);

    // notes cursor
    this->_screen.setPixel(step % 32, 15, true);
    this->_screen.setPixel((step + 31) % 32, 15, false);

    this->_screen.repaint();
}

void Gui::reset()
{
    this->_screen.clear();

    // iterate over 8 bars (chords sequence loop)
    for (uint8_t step = 0; step < 128; step+= 4)
    {
        this->_state.moveToStep(step);

        // draw chord selections (only one channel for now)
        for (uint8_t selectionId = 0; selectionId < 4; selectionId++)
        {
            this->_screen.setPixel(step / 4, (3-selectionId), this->_state.isChordSelected(0, selectionId));
        }
    }

    // iterate over 2 bars (notes sequence loop)
    for (uint8_t step = 0; step < 32; step++)
    {
        this->_state.moveToStep(step);

        // draw note selections
        for (uint8_t selectionId = 0; selectionId < 4; selectionId++)
        {
            this->_screen.setPixel(step, (3-selectionId) + 5, this->_state.isNoteSelected(0, selectionId));
            this->_screen.setPixel(step, (3-selectionId) + 10, this->_state.isNoteSelected(1, selectionId));
        }

        // draw note trigs
        this->_screen.setPixel(step, 9, (this->_state.hasTrigOn(0) != 0));
        this->_screen.setPixel(step, 14, (this->_state.hasTrigOn(1) != 0));
    }

    this->_screen.repaint();
    this->_state.moveToStep(0);
}