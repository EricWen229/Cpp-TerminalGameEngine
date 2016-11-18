#include "EventBuffer.h"

EventBuffer::EventBuffer(): mutex(1) {}

EventBuffer::~EventBuffer() {}

void EventBuffer::put(Event e)
{
    mutex.P();
    q.push(e);
    mutex.V();
    s.V();
}

Event EventBuffer::get()
{
    s.P();
    assert(q.size() > 0);
    mutex.P();
    Event tmp = q.front();
    q.pop();
    mutex.V();
    return tmp;
}
