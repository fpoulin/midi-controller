#ifndef Screen_h
#define Screen_h

#define ARDUINO 1000
#include "LedControl.h"

class Screen {
    public:
        Screen();
        void display(int step);
        void clear(int step);
    private:
        unsigned char r(unsigned char b);
};

#endif // Screen.h