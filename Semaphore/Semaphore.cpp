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

pthread_t createPthread(void *func(void *unused))
{
    pthread_t thread_id;
    pthread_create (&thread_id, NULL, func, NULL);
    return thread_id;
}

void waitPthread(pthread_t thread_id)
{
    pthread_join(thread_id, NULL);
}
