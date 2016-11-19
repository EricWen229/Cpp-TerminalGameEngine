#include "Controller.h"
#include "../Interface/Interface.h"

#define User 1
#define Auto 2

class U: public UserControlThing
{
    public:
        U(): UserControlThing(User)
        {
            look = createArray<char>(3, 3);
            look[0][0] = 'A';
            look[0][1] = 'B';
            look[0][2] = 'C';
            look[1][0] = 'D';
            look[1][1] = 'E';
            look[1][2] = 'F';
            look[2][0] = 'G';
            look[2][1] = 'H';
            look[2][2] = 'I';
            height = width = 3;
        }
        void ifBang(Thing *thing)
        {
        }
        void ifBound(OutBoundType o)
        {
        }
        bool live()
        {
            return  true;
        }
        AutoControlThing *shoot()
        {
            return nullptr;
        }
        ~U()
        {}
};

U *u;

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

class A: public AutoControlThing
{
    public:
        A(): AutoControlThing(Auto)
        {
        }
        void ifBang(Thing &thing)
        {
        }
        void ifBound(int height, int width)
        {
            if (i > height)
            {
                i = height;
            }
            if (j > width)
            {
                j = width;
            }
        }
        bool live()
        {
            return  true;
        }
        void handle()
        {
            i++;
            j++;
        }
};

int main()
{
    Controller c;
    u = new U;
    c.init(20, 80, u, null, 0);
    c.loop();
}
