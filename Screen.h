#pragma once

#define BEGIN_SCREEN_NAMESPACE \
    namespace ui               \
    {
#define END_SCREEN_NAMESPACE }

BEGIN_SCREEN_NAMESPACE

class Screen
{
public:
    Screen();
    void display(int step);
    void clear(int step);

private:
    unsigned char r(unsigned char b);
};

END_SCREEN_NAMESPACE