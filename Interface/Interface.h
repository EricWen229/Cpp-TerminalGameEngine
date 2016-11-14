#ifndef Interface_H
#define Interface_H

#include "../Array/Array.h"
#include "../EventBuffer/EventBuffer.h"
#include <ncurses.h>

/* user interface */
/* interact with user */
class Interface
{
    public:
        /* isExit? */
        typedef bool (*HandleFunc)(Event e);
        virtual void init(SmartArray<char> b, HandleFunc h) = 0;
        virtual void loop() = 0;
        virtual void end() = 0;
};

/* singleton */
/* 类成员函数不能作为线程创建的函数 */
class Ncurses: public Interface
{
    private:
        static WINDOW *win;
        static EventBuffer eb;
        static SmartArray<char> buffer;
        static HandleFunc hf;
        static pthread_t pid[3];
        
        static void *input(void *unused);
        static void *handler(void *unused);
        static void *show(void *unused);
        
    public:
        void init(SmartArray<char>b, HandleFunc h);
        void loop();
        void end();
};

#endif
