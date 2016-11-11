#include "Screen.h"

Screen::Screen(int w, int h): width(w), height(h)
{
    buffer = createArray<char>(width, height);
}

Screen::~Screen() {}

void Screen::print()
{
    assert(!buffer.isNull());
    if (lastBuffer.isNull())
    {
        buffer -> print();
    }
    else
    {
    
    }
}
