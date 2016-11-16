#include "Thing.h"
#include "../Interface/Interface.h"

class U: public UserControlThing
{
    public:
        U(): UserControlThing(User)
        {}
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
};

U u;

void handle(Event e)
{
    switch (e)
    {
        case Up:
            u.i--;
        case Down:
            u.i++;
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
    Ncurses n;
    Controller c;
    c.init(12, 20, &n, null, 0);
    c.loop();
}
