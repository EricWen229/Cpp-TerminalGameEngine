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
            height = width = 3;
        }
        void ifBang(Thing *thing)
        {
        }
        void ifBound(bool, bool, bool, bool)
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

U **u;

void handle(Event e)
{
    switch (e)
    {
        case Up:
            u[0] -> i--;
        case Down:
            u[0] -> i++;
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
    U *uu[] = { new U };
    u = uu;
    c.init(12, 20, &n, (UserControlThing **)uu, 1, null, 0);
    c.loop();
}
