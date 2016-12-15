#include "Interface.h"

Thread Ncurses::pid;
ObjectId Ncurses::sendTo;
bool Ncurses::begin = false;

Implement_Object(Ncurses)
{
    Register_Object(Ncurses);
    Register_Fn(Ncurses, handleMessageUpdate);
    Register_Fn(Ncurses, handleMessageSpriteApp);
    Register_Fn(Ncurses, handleMessageSpriteDis);
}

Ncurses::Ncurses(SmartArray<char>b, ObjectId st):
    Interface(b), DynamicRootObject(-1)
{
    if (!begin)
    {
        begin = true;
        Assert(objectId == -1);
        RegisterObjectInfo();
        
        /* Ncurses::buffer = b; */
        buffer = b;
        sendTo = st;
        
        initscr();
        /* Line bufering disabled */
        /* raw(); */
        /* pass everything to me, don't wait for \n(input) */
        cbreak();
        /* We get F1, F2, arrow, etc */
        keypad(stdscr, true);
        /* Don't echo() while we do getch */
        noecho();
        curs_set(0);
        /* Control the screen size, so we don't use \n. */
        /* 减少刷新缓冲区的次数，提高IO效率 */
        /* 需要为\0字符留出空位，所以width-1 */
        /* Ncurses::win = newwin(buffer -> height, buffer -> width - 1, 0, 0); */
        handleMessageUpdate(null);
        pid = createPthread(std::bind(&Ncurses::input, this, std::placeholders::_1));
    }
    begin = false;
}

Ncurses::~Ncurses() {}

/* template <class T> */
/* void Interface<T>::handleMessageUpdate(void *unused) */
/* { */
/*     int height = buffer -> height, width = buffer -> width; */
/*     for (int i = 0; i < height; i++) */
/*     { */
/*         for (int j = 0; j < width; j++) */
/*         { */
/*             int posI = spriteBitmap[i][j].top().posI; */
/*             int posJ = spriteBitmap[i][j].top().posJ; */
/*             int s = spriteBitmap[i][j].top().objectId; */
/*             Sprite<T> *sprite = (dynamic_cast<Sprite<T> *>(ObjectInfos().getObjectInfo(s) -> getObject())); */
/*             /1* update(i , j, sprite -> getPixel(posI, posJ)); *1/ */
/*         } */
/*     } */
/* } */

void *Ncurses::input(void *unused)
{
    char key;
    while ((key = getchar()) != 'q')
    {
        MailBox().put(Message(objectId, sendTo, "KeyDown", std::string(1, key)));
    }
    return null;
}

void Ncurses::update()
{
    /* buffer[i][j] = pixel; */
    /* /1* mvprintw(i, j, ) *1/ */
    /* mvaddch(i, j,pixel); */
    /* refresh(); */
    for (int i = 0; i < buffer -> height; i++)
    {
        for (int j = 0; j < buffer -> width; j++)
        {
            if (change[i][j])
            {
                mvaddch(i, j, buffer[i][j]);
                change[i][j] = false;
            }
        }
    }
    refresh();
}

void Ncurses::handleMessageUpdate(void *unused)
{
    for (int i = 0; i < buffer -> height; i++)
    {
        mvprintw(i, 0, buffer[i]);
    }
    refresh();
}

void Ncurses::end()
{
    waitPthread(pid);
    endwin();
}
