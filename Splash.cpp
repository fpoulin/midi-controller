#include "Splash.h"

#define NB_FRAMES 100
#define MOVE_IN_FRAMES 60
#define MOVE_OUT_FRAMES 20

// constants are kept in flash memory
const uint8_t __PICTOS[8][5] = {
    {
        (uint8_t)0x3F, // 00111111
        (uint8_t)0x21, // 00100001
        (uint8_t)0x21, // 00100001
        (uint8_t)0xE7, // 11100111
        (uint8_t)0xE7  // 11100111
    },
    {
        (uint8_t)0xCC, // 11001100
        (uint8_t)0x66, // 01100110
        (uint8_t)0x33, // 00110011
        (uint8_t)0x66, // 01100110
        (uint8_t)0xCC  // 11001100
    },
    {
        (uint8_t)0xA2, // 10100010
        (uint8_t)0x08, // 00001000
        (uint8_t)0x51, // 01010001
        (uint8_t)0x88, // 10001000
        (uint8_t)0x22  // 00100010
    },
    {
        (uint8_t)0x49, // 01001001
        (uint8_t)0xDB, // 11011011
        (uint8_t)0x49, // 01001001
        (uint8_t)0xDB, // 11011011
        (uint8_t)0x92  // 10010010
    },
    {
        (uint8_t)0x08, // 00001000
        (uint8_t)0x3E, // 00111110
        (uint8_t)0x1C, // 00011100
        (uint8_t)0x08, // 00001000
        (uint8_t)0xF7  // 11110111
    },
    {
        (uint8_t)0x18, // 00011000
        (uint8_t)0x3D, // 00111101
        (uint8_t)0x67, // 01100111
        (uint8_t)0xC2, // 11000010
        (uint8_t)0x80  // 10000000
    },
    {
        (uint8_t)0x0F, // 00001111
        (uint8_t)0xF0, // 11110000
        (uint8_t)0x0F, // 00001111
        (uint8_t)0xF0, // 11110000
        (uint8_t)0x0F  // 00001111
    },
    {
        (uint8_t)0x00, // 00000000
        (uint8_t)0x00, // 00000000
        (uint8_t)0x55, // 01010101
        (uint8_t)0x00, // 00000000
        (uint8_t)0x00  // 00000000
    }};

Splash::Splash(Screen &screen) : _screen(screen) { }

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

void Splash::play(uint8_t splashPictoId)
{
    this->_pictoId = splashPictoId;
    this->_frame = 0;
    this->_playing = true;
    this->_finished = false;
}

void Splash::loop()
{
    if (this->_playing)
    {
        uint8_t _posXShifted = this->getPosXShifted();

        for (uint8_t x = 0; x < 32; x++)
        {
            for (uint8_t y = 0; y < 5; y++)
            {
                // draw picto
                if (x >= _posXShifted-8 && x <= _posXShifted)
                {
                    this->_bitmap = 128 >> x - (_posXShifted-8);
                    this->_screen.setPixel(x, y, (__PICTOS[this->_pictoId][y] & this->_bitmap) != 0);
                }
                else
                {
                    this->_screen.setPixel(x, y, false);
                }
            }
        }

        // move one frame forward
        if (++this->_frame >= NB_FRAMES)
        {
            this->_playing = false;
            this->_finished = true;
        }
    }
}

// returns the x position of the sprite (shifted by 8 pixels -> unsigned)
uint8_t Splash::getPosXShifted()
{
    // move in: exponential ease out
    if (this->_frame < MOVE_IN_FRAMES)
    {
        float x = this->_frame / (float)MOVE_IN_FRAMES;
        x = x == 1 ? 1 : 1 - pow(2, -10 * x);
        return 20 + floor((1. - x) * 28.); // [20..48]
    }
    // stick around for a bit
    if (this->_frame < NB_FRAMES - MOVE_OUT_FRAMES)
    {
        return 20;
    }

    // move out: exponential ease in
    float x = (this->_frame - (NB_FRAMES - MOVE_OUT_FRAMES)) / (float)MOVE_OUT_FRAMES;
    return floor((1. - x) * 20.); // [0..20]
}