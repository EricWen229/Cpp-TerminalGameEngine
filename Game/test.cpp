#include "../Controller/Controller.h"
#include "../Interface/Interface.h"
#include "../Array/Array.h"
#include "Plane.h"

UserControlThing **u;

void handle(Event e)
{
    switch (e)
    {
        case Up:
            u[0] -> moveAdd(-1, 0);
            break;
        case Down:
            u[0] -> moveAdd(1, 0);
            break;
        case Left:
            u[0] -> moveAdd(0, -1);
            break;
        case Right:
            u[0] -> moveAdd(0, 1);
            break;
    }
}

AutoControlThing *produce()
{
    static int count = 0;
    static Random random(5, 65);
    if (count == 5000)
    {
        count = 0;
        return new Enemy(0, random.get());
    }
    else
    {
        count++;
        return null;
    }
}

int main()
{
    Ncurses n;
    Controller c;
    UserControlThing *uu[] = { new Player };
    u = uu;
    Controller::Producer ps[] = { produce };
    c.init(20, 80, &n, uu, 1, ps, 1);
    c.loop();
}