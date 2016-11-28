#include "Interface.h"

Interface::~Interface() {}

SmartArray<char> Ncurses::buffer;
Thread Ncurses::pid[2];
ObjectId Ncurses::sendTo;
bool Ncurses::exit;

Implement_Class(Ncurses)
{
    Register_Object(Ncurses);
}

Ncurses::Ncurses(): RootObject() {}

Ncurses::~Ncurses()
{
    Out_Object(Ncurses);
}

Ncurses *Ncurses::createObject(void *unusedP)
{
    return new Ncurses;
}

void *Ncurses::input(void *)
{
    char key;
    while ((key = getchar()) != 'q')
    {
        MailBox().put(Message(objectId, sendTo, "KeyDown", std::string(1, key)));
        /* std::cout << key << std::endl; */
    }
    return null;
}

void *Ncurses::show(void *unused)
{
    while (!exit)
    {
        for (int i = 0; i < buffer -> height; i++)
        {
            mvprintw(i, 0, buffer[i]);
        }
        refresh();
    }
    return null;
}

void Ncurses::init(SmartArray<char>b, ObjectId st)
{
    Ncurses::buffer = b;
    sendTo = st;
    exit = false;
    
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
}

void Ncurses::loop()
{
    pid[0] = createPthread(std::bind(&Ncurses::input, this, std::placeholders::_1));
    pid[1] = createPthread(std::bind(&Ncurses::show, this, std::placeholders::_1));
}

void Ncurses::end()
{
    waitPthread(pid[0]);
    exit = true;
    waitPthread(pid[1]);
    
    endwin();
}
