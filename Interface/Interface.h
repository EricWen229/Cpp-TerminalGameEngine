#ifndef Interface_H
#define Interface_H

#include "../Array/Array.h"
#include "Semaphore.h"

enum Event
{
    None, Up, Down, Left, RIght
};

class EventBuffer
{
    private:
        Semaphore s;
        
    public:
        void put(Event event);
        Event get();
};

/* user interface */
/* interact with user */
class Interface
{
    public:
        virtual void init(SmartArray<char> buffer) = 0;
        virtual void loopWork();
};

#endif
