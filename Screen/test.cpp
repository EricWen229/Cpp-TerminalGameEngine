#include "Screen.h"
#include "../Array/Array.h"
#include "../Interface/Interface.h"

SmartArray<char> sa;

void handler(Event e)
{
    switch (e)
    {
        case Up:
            sa[0][0] += 1;
            break;
        case Down:
            sa[0][0] -= 1;
            break;
        case Left:
            break;
        case Right:
            break;
    }
}

int main()
{
    Screen screen;
    Ncurses in;
    screen.init(10, 11, &in, handler);
    int id = screen.alloc(0, 0, 10, 10);
    sa = screen.get(id);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            sa[i][j] = 'f';
        }
    }
    screen.begin();
    screen.end();
}
