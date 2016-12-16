#include "Screen.h"

ScreenChar::ScreenChar(int height, int width):
    Screen<char>(height, width)
{
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();
    curs_set(0);
}
