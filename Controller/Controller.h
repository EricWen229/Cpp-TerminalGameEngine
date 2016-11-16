#ifndef Controller_H
#define Controller_H

#include "../Array/Array.h"
#include "../Screen/Screen.h"
#include <vector>

/* class UserControlThing; */
/* UserControlThing **u; */
void handle(Event e);

/* 为方便扩展，不使用enum，而是用define的方式 */
typedef unsigned int ObjectType;
/* for example */
/* #define UserType 1 */
/* #define AutoType 2 */

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
        /* 给用户自由去决定碰到什么样的物体作什么样的反应 */
        const ObjectType objectType;
        Thing(ObjectType o);
        virtual ~Thing();
        
        void moveTo(int newI, int newJ);
        void moveAdd(int deltaI, int deltaJ);
        
        virtual void ifBound(bool top, bool bottom, bool left, bool right) = 0;
        virtual void ifBang(Thing *thing) = 0;
        virtual AutoControlThing *shoot() = 0;
        virtual bool live() = 0;
};

class UserControlThing: public Thing
{
    public:
        UserControlThing(ObjectType o);
        /* user defined this function by himself */
        friend void handle(Event e);
};

class AutoControlThing: public Thing
{
    public:
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
        
        static std::vector<UserControlThing *> users;
        static std::vector<AutoControlThing *> autos;
        static std::vector<Producer> producers;
        static SmartArray<char> gameBuffer;
        
        static int height, width;
        static Screen screen;
        static std::vector<int> ids;
        
        static void boundHelper(Thing *a);
        void bound();
        bool bangHelper(Thing *a, Thing *b);
        void bang();
        void clean();
        void produce();
        void shoot();
        void handle();
        virtual void draw();
        
    public:
        virtual void init
        (int h, int w, Interface *i,
         UserControlThing *u[], int nUser,
         Producer ps[], int nProducer);
        void loop();
};

#endif
