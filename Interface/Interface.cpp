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
            case 'q':
                eb.put(Quit);
                break;
        }
    }
    return null;
}

void *Ncurses::handler(void *unused)
{
    while (true)
    {
        pthread_testcancel();
        if (hf(eb.get()))
        {
            break;
        }
    }
    return null;
}

void *Ncurses::show(void *unused)
{
    while (true)
    {
        pthread_testcancel();
        for (int i = 0; i < buffer -> height; i++)
        {
            wprintw(win, buffer[i]);
        }
        wrefresh(win);
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
    /* Control the screen size, so we don't use \n. */
    /* 减少刷新缓冲区的次数，提高IO效率 */
    /* 需要为\0字符留出空位，所以width-1 */
    win = newwin(buffer -> height, buffer -> width - 1, 0, 0);
}

void Ncurses::loop()
{
    pthread_t p1 = createPthread(input);
    pthread_t p2 = createPthread(handler);
    pthread_t p3 = createPthread(show);
    
    waitPthread(p1);
    pthread_cancel(p2);
    waitPthread(p2);
    pthread_cancel(p3);
    waitPthread(p3);
}

Ncurses::~Ncurses()
{
    delwin(win);
    endwin();
}
