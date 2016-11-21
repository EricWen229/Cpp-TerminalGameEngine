#include "MailBox.h"

Message::Message(ObjectId f, ObjectId t, Msg m):
    from(f), to(t), msg(m) {}

Message::~Message() {}

std::queue<Message> MailBox::msgs;
Semaphore MailBox::s;
Semaphore MailBox::mutex(1);
Semaphore MailBox::locker(1);
pthread_t MailBox::pid;

void *MailBox::loopHelper(void *unused)
{
    while (true)
    {
        s.P();
        mutex.P();
        Message m = msgs.front();
        if (m.from == Exit && m.to == Exit && m.msg == "")
        {
            break;
        }
        std::function<void *(void *)> handle =
            ObjectInfos().getObjectInfo(m.to) ->
            getDynamicFn("handleMessage");
        locker.P();
        void *paras[2] =
        {
            (void *) &locker,
            (void *) &m
        };
        if (handle != null)
        {
            std::thread(handle, (void *)paras).detach();
        }
        msgs.pop();
        mutex.V();
    }
    return null;
}

MailBox::MailBox() {}

MailBox::~MailBox() {}

void MailBox::put(Message m)
{
    mutex.P();
    msgs.push(m);
    mutex.V();
    s.V();
}

void MailBox::loop()
{
    pid = createPthread(loopHelper);
}

void MailBox::end()
{
    put(Message(Exit, Exit, ""));
    waitPthread(pid);
}
