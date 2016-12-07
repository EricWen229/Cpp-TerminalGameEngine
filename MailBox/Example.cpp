#include "MailBox.h"
#include "../Dynamic/ObjectDynamic.h"
#include <iostream>

class Test: public DynamicRootObject
{
        Declare_Object;
        
    public:
        Test(): DynamicRootObject()
        {
            RegisterObjectInfo();
        }
        virtual ~Test() {}
        void handleMessageInterval(void *pointer)
        {
#ifdef AsyncCallback
            TopHalf(pointer, locker, msg);
            std::cout << msg.msg << std::endl;
            locker.V();
#else
            std::cout << ((Message *)pointer) -> description << std::endl;
#endif
        }
};

Implement_Object(Test)
{
    Register_Object(Test);
    Register_Fn(Test, handleMessageInterval);
}

int main()
{
    MailBox().loop();
    Test t1, t2;
    MailBox().put(Message(t1.objectId, t2.objectId, "Interval", "I love u"));
    MailBox().put(Message(t2.objectId, t1.objectId, "Interval", "I love u, too!"));
    MailBox().end();
    
    /* wait */
    for (int i = 0; i < 100000; i++);
}
