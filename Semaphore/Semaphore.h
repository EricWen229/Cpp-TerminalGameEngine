#ifndef Semaphore_H
#define Semaphore_H

#include <mutex>
#include <condition_variable>

#define UseCppThread

#ifdef UseCppThread
    #include <thread>
    #include <functional>
    typedef std::thread Thread;
#else
    #include <pthread.h>
    typedef pthread_t Thread;
#endif

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

#ifdef UseCppThread
    Thread createPthread(std::function<void *(void *)> func);
    void waitPthread(Thread &thread_id);
#else
    Thread createPthread(void *func(void *unused));
    void waitPthread(Thread thread_id);
#endif

#endif
