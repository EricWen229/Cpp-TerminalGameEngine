#ifndef Plane_H
#define Plane_H

#include "../Controller/Controller.h"
#include "../Interface/Interface.h"
#include "../Array/Array.h"
#include "../Random/Random.h"

#define UserType 0
#define EnemyType 1
#define PlayerBullet 2
#define EnemyBullet 3

extern int AttackTable[4][4];

class Player: public UserControlThing
{
    public:
        int life;
        Player();
        void ifBang(Thing *thing);
        void ifBound(OutBoundType o);
        bool live();
        AutoControlThing *shoot();
};

class Enemy: public AutoControlThing
{
    public:
        int life;
        Enemy(int locI, int locJ);
        void ifBang(Thing *thing);
        void ifBound(OutBoundType o);
        bool live();
        void handle();
        AutoControlThing *shoot();
};

class Bullet: public AutoControlThing
{
    private:
        int di, dj;
        
    public:
        int life;
        Bullet(int posI, int posJ, int speedI, int speedJ, int t);
        void ifBang(Thing *thing);
        void ifBound(OutBoundType o);
        bool live();
        void handle();
        AutoControlThing *shoot();
};

#endif
