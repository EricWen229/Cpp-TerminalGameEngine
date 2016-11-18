#ifndef Semaphore_H
#define Semaphore_H

#include <mutex>
#include <condition_variable>
#include <pthread.h>

#define null nullptr

class Semaphore
{
    private:
        std::mutex mutex;
        std::condition_variable cv;
        int count;
        
    public:
        Semaphore(int c = 0);
        ~Semaphore();
        
        void P();
        void V();
        int get();
};

pthread_t createPthread(void *func(void *unused));
void waitPthread(pthread_t thread_id);

#endif
