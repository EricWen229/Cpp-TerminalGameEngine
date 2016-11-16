#ifndef Plane_H
#define Plane_H

#include "../Controller/Controller.h"
#include "../Interface/Interface.h"
#include "../Array/Array.h"

#define User 1
#define Enemy 2
#define Bullet 3

class Player: public UserControlThing
{
    public:
        int life;
        Player();
        void ifBang(Thing *thing);
        void ifBound(bool top, bool bottom, bool left, bool right);
        bool live();
        AutoControlThing *shoot();
};

class EnemyC: public AutoControlThing
{
    public:
        int life;
        EnemyC();
        void ifBang(Thing *thing);
        void ifBound(bool top, bool bootom, bool left, bool right);
        bool live();
        void handle();
        AutoControlThing *shoot();
};

#endif
