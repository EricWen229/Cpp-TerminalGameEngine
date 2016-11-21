#include "MailBox.h"

Message::Message(ObjectId f, ObjectId t, Msg m):
    from(f), to(t), msg(m) {}

Message::~Message() {}

std::queue<Message> MailBox::msgs;
Semaphore MailBox::s;
Semaphore MailBox::mutex(1);
pthread_t MailBox::pid;

void *MailBox::loopHelper(void *unused)
{
    while (true)
    {
        s.P();
        mutex.P();
        /* 阻塞版本，有可能的话会实现一个非阻塞版本 */
        /* 现阶段的想法是把一个锁传进去，函数拷贝完成之后要释放这个锁 */
        /* 然后我们拿回控制权，就可以修改Message m，调用下一个处理函数 */
        /* 并且不等待线程执行完毕，用dispatch不用join */
        Message m = msgs.front();
        if (m.from == Exit && m.to == Exit && m.msg == "")
        {
            break;
        }
        std::function<void *(void *)> handle =
            ObjectInfos().getObjectInfo(m.to) ->
            getDynamicFn("handleMessage");
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
    pid = createPthread(loopHelper);
}

void MailBox::end()
{
    put(Message(Exit, Exit, ""));
    waitPthread(pid);
}
