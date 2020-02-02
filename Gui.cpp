#include <LedControl.h>
#include "Gui.h"

Gui::Gui(State &state) : _state(state), _screen(Screen())
{
    this->reset();
}

void Gui::moveToStep(uint8_t step)
{
    step = step % 32;
    uint8_t prev = (step + 31) % 32;

    this->_screen.setPixel(step, 10, true);
    this->_screen.setPixel(prev, 10, false);

    this->_screen.repaint();
}

void Gui::reset()
{
    for (uint8_t step = 0; step < 32; step++)
    {
        this->_state.moveToStep(step);

        // draw note selections
        for (uint8_t noteSelectionId = 0; noteSelectionId < 4; noteSelectionId++)
        {
            this->_screen.setPixel(step, (3-noteSelectionId), this->_state.isNoteSelected(0, noteSelectionId));
            this->_screen.setPixel(step, (3-noteSelectionId) + 5, this->_state.isNoteSelected(1, noteSelectionId));
        }

        // draw trigs
        this->_screen.setPixel(step, 4, (this->_state.hasTrigOn(0) != 0));
        this->_screen.setPixel(step, 9, (this->_state.hasTrigOn(1) != 0));
    }

    this->_screen.repaint();
    this->_state.moveToStep(0);
}