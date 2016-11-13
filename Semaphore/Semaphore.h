#ifndef Semaphore_H
#define Semaphore_H

#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#define null nullptr

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short int *array;
    /* struct seminfo *__buf; */
};

class Semaphore
{
    private:
        int sem_id;
        
    public:
        Semaphore(int key, int v = 0);
        ~Semaphore();
        
        void P();
        void V();
};

pthread_t createPthread(void *func(void *unused));
void waitPthread(pthread_t thread_id);

#endif
