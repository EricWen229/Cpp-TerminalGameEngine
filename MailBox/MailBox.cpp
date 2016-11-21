#include "MailBox.h"

Message::Message(ObjectId f, ObjectId t, Msg m):
    from(f), to(t), msg(m) {}

Message::~Message() {}

std::queue<Message> MailBox::msgs;
Semaphore MailBox::s;
Semaphore MailBox::mutex(1);

void *MailBox::loopHelper(void *unused)
{
    while (true)
    {
        s.P();
        mutex.P();
        /* 阻塞版本，有可能的话会实现一个非阻塞版本 */
        Message m = msgs.front();
        std::function<void *(void *)> handle =
            ObjectInfos().getObjectInfo(m.to) ->
            getDynamicFn("handle");
        if (handle != null)
        {
            handle((void *)&m);
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
    std::function<void *(void *)> func = std::bind(&MailBox::loopHelper, this, std::placeholders::_1);
    typedef void *F(void *);
    waitPthread(createPthread(func.target<F>()));
}
