#include "Screen.h"

Screen::Screen(int w, int h): width(w), height(h)
{
    buffer = createArray<char>(width, height);
}

Screen::~Screen() {}

void Screen::print()
{
    if (lastBuffer.isNull())
    {
        if (buffer.isNull())
        {
            return;
        }
        else
        {
            std::cout <<
        }
    }
}
