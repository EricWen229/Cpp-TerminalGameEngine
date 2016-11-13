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
    std::cout << "I produced." << std::endl;
    return null;
}

void *producer2(void *unused)
{
    sleep(1);
    q.push(2);
    s.V();
    sleep(1);
    q.push(3);
    s.V();
    return null;
}

void *customer(void *unused)
{
    s.P();
    /* assert(q.size() != 0); */
    std::cout << q.front() << std::endl;
    q.pop();
    return null;
}

int main()
{
    pthread_t p1 = createPthread(producer);
    pthread_t c1 = createPthread(customer);
    pthread_t c2 = createPthread(customer);
    pthread_t p2 = createPthread(producer);
    
    pthread_t c3 = createPthread(customer);
    pthread_t c4 = createPthread(customer);
    pthread_t p3 = createPthread(producer2);
    
    waitPthread(p1);
    waitPthread(p2);
    waitPthread(c1);
    waitPthread(c2);
    waitPthread(c3);
    waitPthread(c4);
    waitPthread(p3);
}
