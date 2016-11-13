#include "Screen.h"

Screen::Screen(int w, int h, Interface *s)
{
    buffer = createArray<char>(width, height);
}

Screen::~Screen() {}
