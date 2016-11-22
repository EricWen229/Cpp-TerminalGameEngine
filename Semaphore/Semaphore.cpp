#include "Semaphore.h"

Semaphore::Semaphore(int c): count(c) {}

Semaphore::~Semaphore() {}

void Semaphore::P()
{
    std::unique_lock<std::mutex> lock(mutex);
    count--;
    if (count < 0)
    {
        cv.wait(lock);
    }
}

void Semaphore::V()
{
    std::unique_lock<std::mutex> lock(mutex);
    count++;
    if (count <= 0)
    {
        cv.notify_one();
    }
}

int Semaphore::get()
{
    return count;
}

#ifdef UseCppThread
Thread createPthread(std::function<void *(void *)> func)
{
    return std::thread(func, null);
}
void waitPthread(Thread &thread_id)
{
    thread_id.join();
}
#else
Thread createPthread(void *func(void *unused))
{
    Thread thread_id;
    pthread_create (&thread_id, NULL, func, NULL);
    return thread_id;
}
void waitPthread(Thread thread_id)
{
    pthread_join(thread_id, NULL);
}
#endif
