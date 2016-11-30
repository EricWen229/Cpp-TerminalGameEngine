#define LogMode
#define ExtraRunMode

#include "Screen.h"
#include "../MailBox/MailBox.h"
#include "../Array/Array.h"
#include "../DiagHelper.h"

class Test: public RootObject
{
        Declare_Class;
    public:
        SmartArray<char> s;
        
    public:
        Test() {}
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
                    MailBox().put(Message(objectId, -2, "Update", ""));
                    /* std::cout << s[0][0] << std::endl; */
                    break;
                case 's':
                    s[0][0]--;
                    MailBox().put(Message(objectId, -2, "Update", ""));
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
    Screen screen;
    screen.RegisterObjectInfo();
    Test test;
    test.RegisterObjectInfo();
    screen.init(12, 20, test.objectId);
    
    int id1 = screen.alloc(0, 0, 1, 20);
    int id2 = screen.alloc(11, 0, 1, 20);
    int id3 = screen.alloc(1, 0, 10, 1);
    int id4 = screen.alloc(1, 12, 10, 1);
    int id5 = screen.alloc(1, 12, 10, 1);
    int id6 = screen.alloc(1, 1, 10, 11);
    
    SmartArray<char> sa = screen.get(id1);
    for (int i = 1; i < 19; i++)
    {
        sa[0][i] = '-';
    }
    sa[0][0] = sa[0][12] = sa[0][19] = '+';
    /* MailBox().put(Message(-2, -1, "Update", "")); */
    SmartArray<char> sb = screen.get(id2);
    for (int i = 1; i < 19; i++)
    {
        sb[0][i] = '-';
    }
    sb[0][0] = sb[0][12] = sb[0][19] = '+';
    /* MailBox().put(Message(-2, -1, "Update", "")); */
    SmartArray<char> sc = screen.get(id3);
    for (int i = 0; i < 10; i++)
    {
        sc[i][0] = '|';
    }
    Log(Screen::buffer[1] << "Line 85");
    Log(sc[0][0] << "Line 86");
    /* MailBox().put(Message(-2, -1, "Update", "")); */
    /* SmartArray<char> sd = screen.get(id4); */
    /* for (int i = 0; i < 10; i++) */
    /* { */
    /*     sd[i][0] = '|'; */
    /* } */
    /* Log(Screen::buffer[1], "93"); */
    /* Log(sd[0][0], "94"); */
    /* MailBox().put(Message(-2, -1, "Update", "")); */
    SmartArray<char> se = screen.get(id5);
    for (int i = 0; i < 10; i++)
    {
        se[i][0] = '|';
    }
    /* MailBox().put(Message(-2, -1, "Update", "")); */
    SmartArray<char> sf = screen.get(id6);
    ExtraRun(for (int i = 0; i < 12; i++) Log(Screen::buffer[i]););
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            sf[i][j] = 'f';
        }
    }
    for (int i = 0; i < 12; i++)
    {
        Log(Screen::buffer[i]);
    }
    test.s = sf;
    
    MailBox().put(Message(-2, -1, "Update", ""));
    
    screen.end();
}
