#ifndef Interface_H
#define Interface_H

#include "../Array/Array.h"
#include "../Semaphore/Semaphore.h"
#include <queue>
#include <ncurses.h>

enum Event
{
    Up, Down, Left, Right, Quit
};

class EventBuffer
{
    private:
        Semaphore *s;
        std::queue<Event> q;
        
    public:
        EventBuffer();
        ~EventBuffer();
        
        void put(Event event);
        Event get();
};

/* user interface */
/* interact with user */
class Interface
{
    public:
        virtual void init(SmartArray<char> b, void h(Event e)) = 0;
        virtual void loop() = 0;
};

/* singleton */
/* 类成员函数不能作为线程创建的函数 */
class Ncurses: public Interface
{
    private:
        static WINDOW *win;
        static EventBuffer eb;
        static SmartArray<char> buffer;
        
        /* isExit? */
        typedef bool (*HandleFunc)(Event e);
        static HandleFunc hf;
        
        static void *input(void *unused);
        static void *handler(void *unused);
        static void *show(void *unused);
        
    public:
        void init(SmartArray<char>b, HandleFunc h);
        void loop();
        ~Ncurses();
};

#endif
