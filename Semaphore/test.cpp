#include "Semaphore.h"
#include <queue>
#include <iostream>
#include <unistd.h>
#include <assert.h>

Semaphore s(0);
std::queue<int> q;

Semaphore s2(1);

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
    std::cout << "Judge" << (s2.get() != s.get()) << std::endl;
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
    std::cout << "Semaphore's value" << s.get() << std::endl;
    for (int i = 0; i < 8; i++)
    {
        waitPthread(p[i]);
    }
    std::cout << "Judge" << (s.get() == 0) << std::endl;
    
    /* if you add the next line, the program should block. */
    sleep(1);
    pthread_t id = createPthread(customer);
    sleep(1);
    std::cout << "Judge" << (s.get() == -1) << std::endl;
    waitPthread(createPthread(producer2));
    waitPthread(id);
    std::cout << "Judge" << (s.get() == 2) << std::endl;
}
