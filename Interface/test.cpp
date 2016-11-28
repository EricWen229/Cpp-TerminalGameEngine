#include "Interface.h"
#include "../Array/Array.h"
#include <iostream>

class Test: public RootObject
{
        Declare_Class;
    public:
        SmartArray<char> s;
        
    public:
        Test()
        {
            s = createArray<char>(10, 10);
        }
        virtual ~Test() {}
        static Test *createObject(void *unusedP)
        {
            return new Test;
        }
        
        void *handleMessageKeyDown(void *pointer)
        {
            /* std::cout << ((Message *)pointer) -> description << std::endl; */
            switch (((Message *)pointer) -> description.c_str()[0])
            {
                case 'w':
                    s[0][0]++;
                    MailBox().put(Message(objectId, -1, "Update", ""));
                    /* std::cout << s[0][0] << std::endl; */
                    break;
                case 's':
                    s[0][0]--;
                    MailBox().put(Message(objectId, -1, "Update", ""));
                    /* std::cout << s[0][0] << std::endl; */
                    break;
                case 'a':
                    break;
                case 'd':
                    break;
            }
            return null;
        }
};

Implement_Class(Test)
{
    Register_Object(Test);
    Register_Fn(Test, handleMessageKeyDown);
}

int main()
{
    MailBox().loop();
    Ncurses ns;
    Ncurses::RegisterClassInfo();
    ns.RegisterObjectInfo();
    Test test;
    Test::RegisterClassInfo();
    test.RegisterObjectInfo();
    for (int i = 0; i < test.s -> height; i++)
    {
        for (int j = 0; j < test.s -> width; j++)
        {
            test.s[i][j] = 'f';
        }
        test.s[i][test.s -> width - 1] = '\0';
    }
    ns.init(test.s, test.objectId);
    ns.loop();
    ns.end();
    MailBox().end();
}
