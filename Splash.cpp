#include "Splash.h"

Splash::Splash(Screen &screen) : _screen(screen) {}

bool Splash::isPlaying()
{
    return this->_playing;
}

bool Splash::justFinished()
{
    if (this->_finished)
    {
        this->_finished = false;
        return true;
    }
    return false;
}

void Splash::play()
{
    this->_frame = 0;
    this->_playing = true;
    this->_finished = false;
}

void Splash::loop()
{
    if (this->_playing)
    {
        if (this->_frame < 32)
        {
            for (uint8_t x = 0; x < 32; x++)
            {
                for (uint8_t y = 0; y < 16; y++)
                {
                    this->_screen.setPixel(31 - x, 16 - y, this->_frame >= x && this->_frame > y * 2);
                }
            }
        }
        else
        {
            for (uint8_t x = 0; x < 32; x++)
            {
                for (uint8_t y = 0; y < 16; y++)
                {
                    this->_screen.setPixel(31 - x, 16 - y, this->_frame / 2 < x || this->_frame / 2 <= y * 2);
                }
            }
        }

        // move one frame forward
        if (++this->_frame >= 64)
        {
            this->_playing = false;
            this->_finished = true;
        }
    }
}