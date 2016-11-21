#ifndef MailBox_H
#define MailBox_H

#include "../Dynamic/Dynamic.h"
#include "../Semaphore/Semaphore.h"
#include <queue>
#include <functional>

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
        
    private:
        void *loopHelper(void *unused);
        
    public:
        MailBox();
        ~MailBox();
        void put(Message m);
        void loop();
};

#endif
