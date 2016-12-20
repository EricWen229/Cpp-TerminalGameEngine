#include "Timer.h"

void *Timer::loop(void *unused)
{
    while (true)
    {
        for (Iterator it = container.begin(); it != container.end(); it++)
        {
        
        }
    }
    return nullptr;
}

void Timer::reg(ObjectId id, long int usecond, const std::string &name)
{
    container.insert(Container::value_type(usecond,Element(id, name)));
}

void Timer::out(ObjectId id, const std::string &name)
{
    for (Iterator it = container.begin(); it != container.end(); it++)
    {
        ObjectId objectId;
        std::string fN;
        std::tie(objectId, fN) = it -> second;
        if (objectId == id && fN == name)
        {
            container.erase(it);
            break;
        }
    }
}
