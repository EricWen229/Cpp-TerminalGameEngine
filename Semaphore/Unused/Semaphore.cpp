#include "Semaphore.h"

Semaphore::Semaphore(int v)
{
    /* 创建信号量 */
    /* sem_id = semget((key_t)key, 1, 0666 | IPC_CREAT); */
    sem_id  = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    assert(sem_id != -1);
    
    /* 初始化信号量 */
    union semun sem_union;
    sem_union.val = v;
    int res = semctl(sem_id, 0, SETVAL, sem_union);
    assert(res != -1);
}

Semaphore::~Semaphore()
{
    union semun sem_union;
    int res = semctl(sem_id, 0, IPC_RMID, sem_union);
#ifdef DEBUG
    if (res == -1)
    {
        std::cout << errno << std::endl;
        std::cout << EACCES << std::endl;
        std::cout << EFAULT << std::endl;
        std::cout << EIDRM << std::endl;
        std::cout << EINVAL << std::endl;
        std::cout << EPERM << std::endl;
        std::cout << ERANGE << std::endl;
    }
#endif
    assert(res != -1);
}

void Semaphore::P()
{
    struct sembuf sem_b;
    /* sem_num是操作信号在信号集中的编号，第一个信号的编号是0 */
    sem_b.sem_num = 0;
    /* P是获取资源，是-1 */
    sem_b.sem_op = -1;
    /* 避免一些由于异常导致的死锁问题 */
    sem_b.sem_flg = SEM_UNDO;
    
    /* int semop(int semid, struct sembuf *sops, size_t nsops); */
    /* sops是指向存储信号操作结构的数组指针，nsops是这个数组的大小 */
    /* 这个函数实现了一个信号量可以同时有多个操作
     * 但是我们在这里只用一个操作就够了 */
    semop(sem_id, &sem_b, 1);
}

void Semaphore::V()
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1;
    sem_b.sem_flg = SEM_UNDO;
    
    semop(sem_id, &sem_b, 1);
}

int Semaphore::get()
{
    return semctl(sem_id, 0, GETVAL, 0);
}

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
