#include "Interface.h"
#include "../Array/Array.h"
#include <iostream>

class Test: public DynamicRootObject
{
        Declare_Object;
        
    public:
        SmartArray<char> s;
        
    public:
        Test()
        {
            s = createArray<char>(10, 10);
            RegisterObjectInfo();
        }
        virtual ~Test() {}
        
        void handleMessageKeyDown(void *pointer)
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
        }
};

Implement_Object(Test)
{
    Register_Object(Test);
    Register_Fn(Test, handleMessageKeyDown);
}

int main()
{
    MailBox().loop();
    Test test;
    for (int i = 0; i < test.s -> height; i++)
    {
        for (int j = 0; j < test.s -> width; j++)
        {
            test.s[i][j] = 'f';
        }
        test.s[i][test.s -> width - 1] = '\0';
    }
    Ncurses ns(test.s, test.objectId);
    /* ns.init(test.s, test.objectId); */
    /* ns.loop(); */
    ns.end();
    MailBox().end();
}
