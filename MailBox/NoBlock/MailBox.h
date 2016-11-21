#ifndef MailBox_H
#define MailBox_H

#include "../../Dynamic/Dynamic.h"
#include "../../Semaphore/Semaphore.h"
#include <queue>
#include <functional>
#include <thread>

#define FirstAction(p1, p2) \
    void **p2 = (void **)p1; \
    ((Semaphore*)p2[0]) -> V(); \
    p2 = &p2[1];

#define Exit -1

typedef std::string Msg;

class Message
{
    public:
        const ObjectId from;
        const ObjectId to;
        const Msg msg;
        
    public:
        Message(ObjectId f, ObjectId t, Msg m);
        ~Message();
};

class MailBox
{
    private:
        static std::queue<Message> msgs;
        static Semaphore s;
        static Semaphore mutex;
        static Semaphore locker;
        
    private:
        static pthread_t pid;
        static void *loopHelper(void *unused);
        
    public:
        MailBox();
        ~MailBox();
        
        void put(Message m);
        void loop();
        void end();
};

#endif
