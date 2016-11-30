#ifndef Controller_H
#define Controller_H

#include "../Array/Array.h"
#include "../Screen/Screen.h"
#include <vector>
#include <functional>

/* 用反射代替ObjectType的判断 */
/* object.getClasInfo().getName() */

enum OutBoundType
{
    OutBoundTop,
    OutBoundBottom,
    OutBoundLeft,
    OutBoundRight
};

class Controller;
class AutoControlThing;
class Thing
{
    private:
        friend class Controller;
        
    protected:
        int height, width;
        int i, j;
        SmartArray<char> look;
        
    public:
        virtual ~Thing();
        
        void moveTo(int newI, int newJ);
        void moveAdd(int deltaI, int deltaJ);
        
        virtual void ifBound(OutBoundType o) = 0;
        virtual void ifBang(Thing *thing) = 0;
        virtual AutoControlThing *shoot() = 0;
        virtual bool live() = 0;
};

class UserControlThing: public Thing
{
    private:
        friend class Controller;
        
    public:
        virtual ~UserControlThing();
        UserControlThing();
};

class AutoControlThing: public Thing
{
    public:
        virtual ~AutoControlThing();
        AutoControlThing(ObjectType o);
        virtual void handle() = 0;
};

/* singleton */
class Controller
{
    public:
        typedef AutoControlThing *(*Producer)();
        
    private:
        friend class Thing;
        
        static UserControlThing *users;
        static std::vector<AutoControlThing *> autos;
        static std::vector<Producer> producers;
        static SmartArray<char> gameBuffer;
        
        static int height, width;
        static Screen screen;
        static std::vector<int> ids;
        
        static void boundHelper(Thing *a);
        bool bangHelper(Thing *a, Thing *b);
        void bang();
        void clean();
        void produce();
        void shoot();
        void handle();
        void draw();
        
    public:
        virtual void init
        (int h, int w,
         UserControlThing *u,
         Producer ps[], int nProducer);
        void loop();
};

#endif
