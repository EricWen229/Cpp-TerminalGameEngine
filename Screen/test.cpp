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
    screen.init(12, 14, &in, handler);
    int id1 = screen.alloc(1, 0, 10, 10);
    int id2 = screen.alloc(0, 0, 1, 13);
    sa = screen.get(id1);
    SmartArray<char> sb = screen.get(id2);
    for (int i = 1; i < 12; i++)
    {
        sb[0][i] = '-';
    }
    sb[0][0] = '+';
    sb[0][12] = '+';
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
