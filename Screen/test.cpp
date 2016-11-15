#include "Screen.h"
#include "../Interface/Interface.h"

SmartArray<char> sa;

void handler(Event e)
{
    switch (e)
    {
        case Up:
            std::cout << sa[0][0] << std::endl;
            sa[0][0] += 1;
            break;
        case Down:
            std::cout << 'd' << std::endl;
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
    screen.begin();
    screen.end();
}
