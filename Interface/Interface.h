#ifndef Interface_H
#define Interface_H

#include "../Array/Array.h"
#include "../Semaphore/Semaphore.h"
#include <queue>

enum Event
{
    Up, Down, Left, Right
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
        virtual void init(SmartArray<char> buffer) = 0;
        virtual void loop();
};

#endif
