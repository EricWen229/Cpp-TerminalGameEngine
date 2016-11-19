#ifndef Interface_H
#define Interface_H

#include "../Array/Array.h"
#include "../EventBuffer/EventBuffer.h"
#include <functional>
#include <ncurses.h>

/* user interface */
/* interact with user */
class Interface
{
    public:
        /* isExit? */
        typedef void (*HandleFunc)(Event e);
        virtual void init(SmartArray<char> b, HandleFunc h) = 0;
        virtual void loop() = 0;
        virtual void end() = 0;
        virtual bool isExit() = 0;
};

/* singleton */
class Ncurses: public Interface
{
    private:
        static EventBuffer eb;
        static SmartArray<char> buffer;
        static HandleFunc hf;
        static pthread_t pid[3];
        static bool exit;
        
        static void *input(void *unused);
        static void *handler(void *unused);
        static void *show(void *unused);
        
    public:
        void init(SmartArray<char>b, HandleFunc h);
        void loop();
        void end();
        bool isExit();
};

#endif
