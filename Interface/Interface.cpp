#include "Interface.h"

EventBuffer::EventBuffer()
{
    s = new Semaphore(1000);
}

EventBuffer::~EventBuffer()
{
    delete s;
}

void EventBuffer::put(Event e)
{
    q.push(e);
    s -> V();
}

Event EventBuffer::get()
{
    s -> P();
    Event tmp = q.front();
    q.pop();
    return tmp;
}

void *Ncurses::input(void *)
{
    char key;
    while ((key = getch()) != 'q')
    {
        switch (key)
        {
            case 'w':
                eb.put(Up);
                break;
            case 's':
                eb.put(Down);
                break;
            case 'a':
                eb.put(Left);
                break;
            case 'd':
                eb.put(Right);
                break;
        }
    }
    return null;
}

void *Ncurses::handler(void *unused)
{
    while (true)
    {
        if (hf(eb.get()))
        {
            break;
        }
    }
    return null;
}

void Ncurses::init(SmartArray<char>b, HandleFunc h)
{
    buffer = b;
    hf = h;
    
    initscr();
    /* Line bufering disabled(input) */
    raw();
    /* We get F1, F2, arrow, etc */
    keypad(stdscr, true);
    /* Don't echo() while we do getch */
    noecho();
}

void Ncurses::loop()
{
    createPthread(input);
    createPthread(handler);
}
