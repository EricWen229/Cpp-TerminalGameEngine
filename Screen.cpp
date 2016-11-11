#include "Screen.h"

Screen::Screen(int w, int h, Show *s): width(w), height(h), show(s)
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
