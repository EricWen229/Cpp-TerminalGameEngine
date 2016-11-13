#include "Semaphore.h"
#include <queue>
#include <iostream>
#include <unistd.h>

Semaphore s(1000, 0);
std::queue<int> q;

void *producer(void *unused)
{
    sleep(1);
    q.push(1);
    s.V();
    sleep(1);
    q.push(2);
    s.V();
    sleep(1);
    q.push(3);
    s.V();
    return null;
}

void *producer2(void *unused)
{
    q.push(4);
    s.V();
    q.push(5);
    s.V();
    q.push(6);
    s.V();
    return null;
}

void *customer(void *unused)
{
    s.P();
    assert(q.size() > 0);
    std::cout << q.front() << std::endl;
    q.pop();
    return null;
}

int main()
{
    pthread_t p[] =
    {
        /* three customer should wait for 1, 2, 3 seconds */
        createPthread(customer),
        createPthread(customer),
        createPthread(customer),
        createPthread(customer),
        createPthread(customer),
        createPthread(customer),
        createPthread(producer),
        createPthread(producer2)
    };
    for (int i = 0; i < 8; i++)
    {
        waitPthread(p[i]);
    }
    std::cout << (s.get() == 0) << std::endl;
    
    /* if you add the next line, the program should block. */
    sleep(1);
    pthread_t id = createPthread(customer);
    sleep(1);
    std::cout << (s.get() == -1) << std::endl;
    waitPthread(id);
}
