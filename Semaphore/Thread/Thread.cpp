#include "Thread.h"

std::thread createPthread(std::function<void *(void *)> func)
{
    return std::thread(func, null);
}

void waitPthread(std::thread &thread)
{
    thread.join();
}
