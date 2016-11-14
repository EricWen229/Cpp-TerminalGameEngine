#include "EventBuffer.h"

EventBuffer::EventBuffer()
{
    s = new Semaphore();
}

EventBuffer::~EventBuffer()
{
    delete s;
}

void EventBuffer::put(Event e)
{
    q.push(e);
    s -> V();
}

Event EventBuffer::get()
{
    s -> P();
    assert(q.size() > 0);
    Event tmp = q.front();
    q.pop();
    return tmp;
}
