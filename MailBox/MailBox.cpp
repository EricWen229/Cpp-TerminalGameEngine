#include "MailBox.h"

Message::Message(ObjectId f, ObjectId t, Type ty, Description d):
    from(f), to(t), type(ty), description(d) {}

Message::~Message() {}

std::queue<Message> MailBox::msgs;
Semaphore MailBox::s;
Semaphore MailBox::mutex(1);
#ifdef AsyncCallback
    Semaphore MailBox::locker(1);
#endif
Thread MailBox::pid;

void *MailBox::loopHelper(void *unused)
{
    while (true)
    {
        s.P();
        mutex.P();
        Message m = msgs.front();
        if (m.type == "Exit")
        {
            break;
        }
        std::function<void *(void *)> handle =
            ObjectInfos().getObjectInfo(m.to) ->
            getDynamicFn(std::string("handleMessage") + m.type);
#ifdef AsyncCallback
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
#else
        if (handle != null)
        {
            handle((void *)&m);
        }
#endif
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
    put(Message(0, 0, "Exit", ""));
    waitPthread(pid);
}
