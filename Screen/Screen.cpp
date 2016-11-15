#include "Screen.h"

Interface *Screen::interface;
SmartArray<char> Screen::buffer;
int Screen::width, Screen::height;
std::vector<ManBook> Screen::books;
Interface::HandleFunc Screen::handleFunc;
pthread_t Screen::pid;

void *Screen::runHelper(void *unused)
{
    interface -> init(buffer, handleFunc);
    interface -> loop();
    interface -> end();
    return null;
}

void Screen::init(
    int h, int w,
    Interface *in,
    Interface::HandleFunc hf)
{
    height = h;
    width = w;
    buffer = createArray<char>(width, height);
    interface = in;
    handleFunc = hf;
}

void Screen::begin()
{
    pid = createPthread(runHelper);
}

void Screen::end()
{
    waitPthread(pid);
}

Id Screen::alloc(int top, int left, int height, int width)
{
    int size = books.size();
    /* for (int i = 0; i < size; i++) */
    /* { */
    /*     if */
    /*     ( */
    /*         books[i].left + width > left && */
    /*         books[i].top + width > top */
    /*     ) */
    /*     { */
    /*         return -1; */
    /*     } */
    /* } */
    
    ManBook book;
    book.left = left;
    book.top = top;
    book.height = height;
    book.width = width;
    
    books.push_back(book);
    return size;
}

SmartArray<char> Screen::get(Id id)
{
    if (id == -1)
    {
        return SmartArray<char>();
    }
    else
    {
        ManBook book = books[id];
        return createArray(book.top, book.left, book.height, book.width, buffer);
    }
}

void Screen::free(Id id)
{
    if (id == -1)
    {
        return;
    }
    else
    {
        books.erase(books.begin() + id);
    }
}
