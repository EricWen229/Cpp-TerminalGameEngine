#include "Interface.h"
#include "../Semaphore/Semaphore.h"
#include <iostream>

EventBuffer eb;

void *get(void *unused)
{
    Event e = eb.get();
    std::cout << e << std::endl;
    return null;
}

void *put(void *unused)
{
    eb.put(Up);
    eb.put(Right);
    eb.put(Left);
    return null;
}

int main()
{
    pthread_t p1 = createPthread(get);
    /* pthread_t p2 = createPthread(put); */
    pthread_t p3 = createPthread(get);
    
    char c;
    for (int i = 0; i < 2; i++)
    {
        std::cin >> c;
        eb.put(Up);
    }
    
    waitPthread(p1);
    /* waitPthread(p2); */
    waitPthread(p3);
}
