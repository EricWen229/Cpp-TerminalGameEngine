#include "Screen.h"

Interface *Screen::interface;
SmartArray<char> Screen::buffer;
int Screen::width, Screen::height;
std::vector<ManBook> Screen::books;

Screen::Screen(int w, int h, Interface *i)
{
    width = w;
    height = h;
    buffer = createArray<char>(width, height);
    interface = i;
}

Screen::~Screen() {}

Id Screen::alloc(int top, int left, int height, int width)
{
    int size = books.size();
    for (int i = 0; i < size; i++)
    {
        if
        (
            books[i].left + width > left &&
            books[i].top + width > top
        )
        {
            return -1;
        }
    }
    
    ManBook book;
    book.left = left;
    book.top = top;
    book.height = height;
    book.width = width;
    
    books[size] = book;
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
        ManBook book = books[books.size() - 1];
        return createArray(book.top, book.left, book.height, book.width, buffer);
    }
}

/* void Screen::free(Id id) */
/* { */
/*     if (id == -1) */
/*     { */
/*         return; */
/*     } */
/*     else */
/*     { */
/*         books.erase(books.begin() + id); */
/*     } */
/* } */

void Screen::run()
{
    interface -> init();
    interface -> loop();
    interface -> end();
}
