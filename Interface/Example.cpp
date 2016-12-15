#include "Interface.h"
#include "../Array/Array.h"
#include "Sprite.h"
#include <iostream>

class Background: public Sprite<char>
{
        Declare_Object;
    public:
        Background(): Sprite(0, 0, 10, 10, 0)
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

int main()
{
    MailBox().loop();
    Fly fly;
    SmartArray<char> buffer = createArray<char>(20, 20);
    Ncurses ns(buffer, fly.objectId);
    Background back;
    MailBox().putAsync(Message(back.objectId, -1, "SpriteApp", ""));
    MailBox().putAsync(Message(fly.objectId, -1, "SpriteApp", ""));
    ns.end();
    MailBox().end();
}
