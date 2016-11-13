#include "Interface.h"

EventBuffer::EventBuffer()
{
    s = new Semaphore(1000);
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
    Event tmp = q.front();
    q.pop();
    return tmp;
}
