#include "EventBuffer.h"

EventBuffer::EventBuffer()
{
    s = new Semaphore;
    mutex = new Semaphore(1);
}

EventBuffer::~EventBuffer()
{
    delete s;
    delete mutex;
}

void EventBuffer::put(Event e)
{
    mutex -> P();
    q.push(e);
    mutex -> V();
    s -> V();
}

Event EventBuffer::get()
{
    s -> P();
    mutex -> P();
    assert(q.size() > 0);
    Event tmp = q.front();
    q.pop();
    mutex -> V();
    return tmp;
}
