#include <iostream>
#include <unistd.h>
#include "Interface.h"

EventBuffer eb;

void *get(void *unused)
{
    Event e = eb.get();
    std::cout << e << std::endl;
    return null;
}

void *put(void *unused)
{
    sleep(1);
    eb.put(Up);
    sleep(2);
    eb.put(Right);
    eb.put(Left);
    return null;
}

int main()
{
    pthread_t p[] =
    {
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(put)
    };
    
    for (int i = 0; i < 4; i++)
    {
        waitPthread(p[i]);
    }
    
    /* add next line should cause block; */
    /* waitPthread(createPthread(get)); */
}
