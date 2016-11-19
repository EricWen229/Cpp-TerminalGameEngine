#include "../Controller/Controller.h"
#include "../Interface/Interface.h"
#include "../Array/Array.h"
#include "Plane.h"

UserControlThing *u;

void handle(Event e)
{
    switch (e)
    {
        case Up:
            u -> moveAdd(-1, 0);
            break;
        case Down:
            u -> moveAdd(1, 0);
            break;
        case Left:
            u -> moveAdd(0, -1);
            break;
        case Right:
            u -> moveAdd(0, 1);
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
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
            {
                AttackTable[i][j] = 0;
            }
            else
            {
                AttackTable[i][j] = 2;
            }
        }
    }
    Controller c;
    u = new Player;
    Controller::Producer ps[] = { produce };
    c.init(20, 80, u, ps, 1);
    c.loop();
}
