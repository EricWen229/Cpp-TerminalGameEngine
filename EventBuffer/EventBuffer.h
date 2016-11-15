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
        /* 不是STL的锅，不需要互斥使用队列 */
        Semaphore *mutex;
        std::queue<Event> q;
        
    public:
        EventBuffer();
        ~EventBuffer();
        
        void put(Event event);
        Event get();
};

#endif
