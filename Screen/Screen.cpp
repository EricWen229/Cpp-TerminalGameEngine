#include "Screen.h"

ObjectId Screen::objectId = -2;
Interface &Screen::interface = *(new Ncurses);
SmartArray<char> Screen::buffer;
int Screen::width, Screen::height;
std::vector<ManBook> Screen::books;
ObjectId Screen::sendTo;

Implement_Class(Screen)
{
    Register_Object(Screen);
    Register_Fn(Screen, handleMessageUpdate);
    Register_Fn(Screen, handleMessageKeyDown);
}

Screen::Screen() {}
Screen::~Screen() {}

Screen *Screen::createObject(void *unusedP)
{
    return new Screen;
}

void Screen::init(int h, int w, ObjectId st)
{
    height = h;
    width = w;
    buffer = createArray<char>(height, width + 1);
    sendTo = st;
    interface.init(buffer, sendTo);
    interface.loop();
}

void Screen::end()
{
    interface.end();
}

void *Screen::handleMessageUpdate(void *pointer)
{
    Message tmp = *((Message *)pointer);
    Message msg(tmp.from, -1, tmp.type, tmp.description);
    MailBox().put(msg);
    return null;
}

void *Screen::handleMessageKeyDown(void *pointer)
{
    Message tmp = *((Message *)pointer);
    Message msg(objectId, sendTo, tmp.type, tmp.description);
    MailBox().put(msg);
    return null;
}

Id Screen::alloc(int top, int left, int height, int width)
{
    int size = books.size();
    /* shoud check valid here */
    
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
