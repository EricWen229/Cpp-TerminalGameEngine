#ifndef MailBox_H
#define MailBox_H

#include "../Dynamic/Dynamic.h"
#include "../Semaphore/Semaphore.h"
#include <queue>
#include <functional>

/* #define AsyncCallback */

#ifdef AsyncCallback
#include <thread>
#define TopHalf(para, locker, message) \
    void **avoidConflictWithUser = (void **)para; \
    Semaphore &locker = *((Semaphore *)avoidConflictWithUser[0]); \
    Message &message = *((Message *)avoidConflictWithUser[1]);
#endif

#define Exit -1

typedef std::string Type;
typedef std::string Description;

class Message
{
    public:
        const ObjectId from;
        const ObjectId to;
        const Type type;
        const Description description;
        
    public:
        Message(ObjectId f, ObjectId t, Type ty, Description d);
        ~Message();
};

class MailBox
{
    private:
        static std::queue<Message> msgs;
        static Semaphore s;
        static Semaphore mutex;
#ifdef AsyncCallback
        static Semaphore locker;
#endif
        
    private:
        static Thread pid;
        static void *loopHelper(void *unused);
        
    public:
        MailBox();
        ~MailBox();
        
        void put(Message m);
        void loop();
        void end();
};

#endif
