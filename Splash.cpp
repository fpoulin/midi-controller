#include "Splash.h"

#define NB_FRAMES 100
#define MOVE_IN_FRAMES 60
#define MOVE_OUT_FRAMES 20

#include <avr/pgmspace.h>

// put pictos in flash memory (progmem)
const uint8_t __PICTOS[8][5] PROGMEM = {
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
        (uint8_t)0x18, // 00011000
        (uint8_t)0x3D, // 00111101
        (uint8_t)0x67, // 01100111
        (uint8_t)0xC2, // 11000010
        (uint8_t)0x80  // 10000000
    },
    {
        (uint8_t)0x08, // 00001000
        (uint8_t)0x3E, // 00111110
        (uint8_t)0x1C, // 00011100
        (uint8_t)0x08, // 00001000
        (uint8_t)0xF7  // 11110111
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

// put numbers in flash memory (progmem)
const uint8_t __NUMBERS[16][5] PROGMEM = {
    {
        (uint8_t)0x18, // 00011000
        (uint8_t)0x08, // 00001000
        (uint8_t)0x08, // 00001000
        (uint8_t)0x08, // 00001000
        (uint8_t)0x1C  // 00011100
    },
    {
        (uint8_t)0x3C, // 00111100
        (uint8_t)0x04, // 00000100
        (uint8_t)0x3C, // 00111100
        (uint8_t)0x20, // 00100000
        (uint8_t)0x3C  // 00111100
    },
    {
        (uint8_t)0x3C, // 00111100
        (uint8_t)0x04, // 00000100
        (uint8_t)0x1C, // 00011100
        (uint8_t)0x04, // 00000100
        (uint8_t)0x3C  // 00111100
    },
    {
        (uint8_t)0x20, // 00100000
        (uint8_t)0x20, // 00100000
        (uint8_t)0x28, // 00101000
        (uint8_t)0x3C, // 00111100
        (uint8_t)0x08  // 00001000
    },
    {
        (uint8_t)0x3C, // 00111100
        (uint8_t)0x20, // 00100000
        (uint8_t)0x3C, // 00111100
        (uint8_t)0x04, // 00000100
        (uint8_t)0x3C  // 00111100
    },
    {
        (uint8_t)0x3C, // 00111100
        (uint8_t)0x20, // 00100000
        (uint8_t)0x3C, // 00111100
        (uint8_t)0x24, // 00100100
        (uint8_t)0x3C  // 00111100
    },
    {
        (uint8_t)0x3C, // 00111100
        (uint8_t)0x04, // 00000100
        (uint8_t)0x04, // 00000100
        (uint8_t)0x04, // 00000100
        (uint8_t)0x04  // 00000100
    },
    {
        (uint8_t)0x3C, // 00111100
        (uint8_t)0x24, // 00100100
        (uint8_t)0x3C, // 00111100
        (uint8_t)0x24, // 00100100
        (uint8_t)0x3C  // 00111100
    },
    {
        (uint8_t)0x3C, // 00111100
        (uint8_t)0x24, // 00100100
        (uint8_t)0x3C, // 00111100
        (uint8_t)0x04, // 00000100
        (uint8_t)0x3C  // 00111100
    },
    {
        (uint8_t)0xCF, // 11001111
        (uint8_t)0x49, // 01001001
        (uint8_t)0x49, // 01001001
        (uint8_t)0x49, // 01001001
        (uint8_t)0xEF  // 11101111
    },
    {
        (uint8_t)0xCC, // 11001100
        (uint8_t)0x44, // 01000100
        (uint8_t)0x44, // 01000100
        (uint8_t)0x44, // 01000100
        (uint8_t)0xEE  // 11101110
    },
    {
        (uint8_t)0xCF, // 11001111
        (uint8_t)0x41, // 01000001
        (uint8_t)0x4F, // 01001111
        (uint8_t)0x48, // 01001000
        (uint8_t)0xEF  // 11101111
    },
    {
        (uint8_t)0xCF, // 11001111
        (uint8_t)0x41, // 01000001
        (uint8_t)0x47, // 01000111
        (uint8_t)0x41, // 01000001
        (uint8_t)0xEF  // 11101111
    },
    {
        (uint8_t)0xC8, // 11001000
        (uint8_t)0x4A, // 01001010
        (uint8_t)0x4A, // 01001010
        (uint8_t)0x4F, // 01001111
        (uint8_t)0xE2  // 11100010
    },
    {
        (uint8_t)0xCF, // 11001111
        (uint8_t)0x48, // 01001000
        (uint8_t)0x4F, // 01001111
        (uint8_t)0x41, // 01000001
        (uint8_t)0xEF  // 11101111
    },
    {
        (uint8_t)0xC8, // 11001000
        (uint8_t)0x48, // 01001000
        (uint8_t)0x4F, // 01001111
        (uint8_t)0x49, // 01001001
        (uint8_t)0xEF  // 11101111
    }};
    
Splash::Splash(Screen &screen) : _screen(screen) { }

bool Splash::isPlaying()
{
    return _playingPicto || _showingNumber;
}

void Splash::playPicto(uint8_t splashPictoId, SplashCallback &onFinish)
{
    _pictoId = splashPictoId;
    _frame = 0;
    _playingPicto = true;
    _showingNumber = false;
    _onFinish = &onFinish;

    // copy __PICTOS[_pictoId] to buffer
    memcpy_P(_buffer, __PICTOS[_pictoId], 5);
}

void Splash::showNumber(uint8_t number, SplashCallback &onFinish)
{
    _numberId = number-1;
    _frame = 0;
    _playingPicto = false;
    _showingNumber = true;
    _onFinish = &onFinish;

    // copy __NUMBERS[numberId] to buffer
    memcpy_P(_buffer, __NUMBERS[_numberId], 5);
}

void Splash::loop()
{
    if (_playingPicto)
    {
        uint8_t _posXShifted = getPosXShifted();

        for (uint8_t x = 0; x < 32; x++)
        {
            for (uint8_t y = 0; y < 5; y++)
            {
                // draw picto
                if (x >= _posXShifted-8 && x <= _posXShifted)
                {
                    _bitmap = 128 >> x - (_posXShifted-8);
                    _screen.setPixel(x, y, (_buffer[y] & _bitmap) != 0);
                }
                else
                {
                    _screen.setPixel(x, y, false);
                }
            }
        }

        // move one frame forward
        if (++_frame >= NB_FRAMES)
        {
            _playingPicto = false;
            _onFinish->onSplashEnd();
        }
    }
    else if (_showingNumber)
    {
        for (uint8_t x = 0; x < 32; x++)
        {
            for (uint8_t y = 0; y < 5; y++)
            {
                // draw number
                if (x >= 12 && x <= 20)
                {
                    _bitmap = 128 >> x - 12;
                    _screen.setPixel(x, y, (_buffer[y] & _bitmap) != 0);
                }
                else
                {
                    _screen.setPixel(x, y, false);
                }
            }
        }

        // move one frame forward
        if (++_frame >= NB_FRAMES / 2)
        {
            _showingNumber = false;
            _onFinish->onSplashEnd();
        }
    }
}

// returns the x position of the sprite (shifted by 8 pixels -> unsigned)
uint8_t Splash::getPosXShifted()
{
    // move in: exponential ease out
    if (_frame < MOVE_IN_FRAMES)
    {
        float x = _frame / (float)MOVE_IN_FRAMES;
        x = x == 1 ? 1 : 1 - pow(2, -10 * x);
        return 20 + floor((1. - x) * 28.); // [20..48]
    }
    // stick around for a bit
    if (_frame < NB_FRAMES - MOVE_OUT_FRAMES)
    {
        return 20;
    }

    // move out: exponential ease in
    float x = (_frame - (NB_FRAMES - MOVE_OUT_FRAMES)) / (float)MOVE_OUT_FRAMES;
    return floor((1. - x) * 20.); // [0..20]
}