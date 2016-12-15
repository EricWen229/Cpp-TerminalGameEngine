#include "Interface.h"

Thread Ncurses::pid;
ObjectId Ncurses::sendTo;
bool Ncurses::begin = false;

Ncurses::Ncurses(SmartArray<char>b, ObjectId st):
    Interface(b)
{
    if (!begin)
    {
        begin = true;
        Assert(objectId == -1);
        
        sendTo = st;
        
        initscr();
        cbreak();
        keypad(stdscr, true);
        noecho();
        curs_set(0);
        pid = createPthread(std::bind(&Ncurses::input, this, std::placeholders::_1));
    }
    begin = false;
}

Ncurses::~Ncurses() {}

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

void Ncurses::end()
{
    waitPthread(pid);
    endwin();
}
