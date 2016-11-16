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
        void ifBound(bool, bool, bool, bool);
        bool live();
        AutoControlThing *shoot();
};
