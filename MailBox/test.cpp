#include "MailBox.h"
#include "../Dynamic/Dynamic.h"
#include <iostream>
#define AsyncCallback

class Test: public RootObject
{
        Declare_Class;
    public:
        Test(): RootObject() {}
        virtual ~Test()
        {
            Out_Object(Test);
        }
        void *handleMessage(void *pointer)
        {
#ifndef AsyncCallback
            std::cout << ((Message *)pointer) -> msg << std::endl;
#else
            TopHalf(pointer, locker, msg);
            std::cout << msg.msg << std::endl;
            locker.V();
#endif
            return null;
        }
        static void *createObject(void *)
        {
            return null;
        }
};

Implement_Class(Test)
{
    Register_Object(Test);
    Register_Fn(Test, handleMessage);
}

int main()
{
    MailBox().loop();
    Test t1, t2;
    t1.RegisterObjectInfo();
    t2.RegisterObjectInfo();
    MailBox().put(Message(t1.objectId, t2.objectId, "I love u"));
    MailBox().put(Message(t2.objectId, t1.objectId, "I love u, too!"));
    MailBox().end();
}
