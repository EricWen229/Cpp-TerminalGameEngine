#include "Thread.h"
#include <iostream>

#define null nullptr

void *f(void *unused)
{
    std::cout << "Hi!" << std::endl;
    return null;
}

int main()
{
    std::thread threads[] =
    {
        createPthread(std::bind(f, std::placeholders::_1)),
        createPthread(f)
    };
    for (int i = 0; i < 2; i++)
    {
        waitPthread(threads[i]);
    }
}
