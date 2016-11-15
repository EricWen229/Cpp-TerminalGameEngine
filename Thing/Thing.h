#ifndef Thing_H
#define Thing_H

#include "../Array/Array.h"
#include "../Screen/Screen.h"
#include <vector>

void handle(Event e);

enum ObjectType
{
    /* for example */
    Object1
};

class Controller;
class Thing
{
    private:
        friend class Controller;
        
    protected:
        int height, width;
        int x, y;
        SmartArray<char> look;
        
    public:
        /* 给用户自由去决定碰到什么样的物体作什么样的反应 */
        const ObjectType objectType;
        Thing(ObjectType o);
        virtual ~Thing();
        
        virtual void ifBang(Thing &thing) = 0;
        virtual void ifBound(int h, int w) = 0;
        virtual bool live() = 0;
};

class UserControlThing: public Thing
{
    public:
        /* user defined this function by himself */
        friend void handle(Event e);
};

class AutoControlThing: public Thing
{
    public:
        virtual void handle() = 0;
};

/* singleton */
class Controller
{
    public:
        typedef Thing *(*Producer)();
        
    private:
        static std::vector<Thing *> things;
        static std::vector<Producer> producers;
        static int height, width;
        static bool exit;
        static Screen screen;
        static SmartArray<char> buffer;
        
        void bang();
        void bound();
        void clean();
        virtual void produce();
        void handle();
        void draw();
        
    public:
        void init(int h, int w, Interface *i, Producer ps[], int nProducer);
        void loop();
};

#endif