#ifndef EventBuffer_H
#define EventBuffer_H

#include "../Semaphore/Semaphore.h"
#include <queue>

enum Event
{
    Up, Down, Left, Right, Exit
};

class EventBuffer
{
    private:
        Semaphore *s;
        Semaphore *mutex;
        std::queue<Event> q;
        
    public:
        EventBuffer();
        ~EventBuffer();
        
        void put(Event event);
        Event get();
};

#endif
