#include "Interface.h"
#include "../Array/Array.h"
#include "Sprite.h"
#include <iostream>

class Background: public Sprite<char>
{
        Declare_Object;
    public:
        Background(): Sprite(0, 0, 10, 10)
        {
            appear = createArray<char>(10, 10);
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    appear[i][j] = 'B';
                }
            }
            RegisterObjectInfo();
        }
};

Implement_Object(Background)
{
    Register_Object(Background);
}

class Fly: public Sprite<char>
{
        Declare_Object;
    public:
        void handleMessageKeyDown(void *pointer)
        {
            switch (((Message *)pointer) -> description.c_str()[0])
            {
                case 'w':
                    moveAdd(-1, 0);
                    break;
                case 's':
                    moveAdd(1, 0);
                    break;
                case 'a':
                    moveAdd(0, -1);
                    break;
                case 'd':
                    moveAdd(0, 1);
                    break;
            }
        }
        Fly(): Sprite(0, 0, 3, 3)
        {
            appear = createArray<char>(3, 3);
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    appear[i][j] = 'A';
                }
            }
            RegisterObjectInfo();
        }
        ~Fly() {}
};

Implement_Object(Fly)
{
    Register_Object(Fly);
    Register_Fn(Fly, handleMessageKeyDown);
}

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
    Fly fly;
    SmartArray<char> buffer = createArray<char>(20, 20);
    Ncurses ns(buffer, fly.objectId);
    Background back;
    MailBox().putAsync(Message(back.objectId, -1, "SpriteApp", ""));
    MailBox().putAsync(Message(fly.objectId, -1, "SpriteApp", ""));
    /* Test test; */
    /* for (int i = 0; i < test.s -> height; i++) */
    /* { */
    /*     for (int j = 0; j < test.s -> width; j++) */
    /*     { */
    /*         test.s[i][j] = 'f'; */
    /*     } */
    /*     test.s[i][test.s -> width - 1] = '\0'; */
    /* } */
    /* Ncurses ns(test.s, test.objectId); */
    /* ns.init(test.s, test.objectId); */
    /* ns.loop(); */
    ns.end();
    MailBox().end();
}
