#include "Interface.h"
#include "../Semaphore/Semaphore.h"
#include "../Array/Array.h"
#include <iostream>

SmartArray<char> s = createArray<char>(10, 10);

bool handler(Event e)
{
    switch (e)
    {
        case Up:
            s[0][0] += 1;
            break;
        case Down:
            s[0][0] -= 1;
            break;
        case Left:
            break;
        case Right:
            break;
    }
    return false;
}

int main()
{
    Ncurses ns;
    for (int i = 0; i < s -> height; i++)
    {
        for (int j = 0; j < s -> width; j++)
        {
            s[i][j]='f';
        }
        s[i][s -> width - 1] = '\0';
    }
    ns.init(s, handler);
    ns.loop();
    ns.end();
}
