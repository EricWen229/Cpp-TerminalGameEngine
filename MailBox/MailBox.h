#ifndef MailBox_H
#define MailBox_H

#include "../Dynamic/ObjectDynamic.h"
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

/* 发送消息的对象用from指代 */
/* 接收消息的对象用to指代 */
/* 要发送消息和接收消息的对象请继承一次RootObject（只继承一次，父亲类继承过则子类不需要也不应该继承） */
/* 信息类型是type */
/* 则相应的对象要实现handleMessagetype函数 */
/* 框架的使用者只需要定义相应的handleMessagetype函数就可以使用该消息 */
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
        /* static Semaphore mutex; */
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
