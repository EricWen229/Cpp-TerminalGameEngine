#ifndef Screen_H
#define Screen_H

#include "../Array/Array.h"
#include "Interface.h"
#include "NoticeBoard.h"
#include <vector>
#include <ncurses.h>

typedef int Id;

/* manage book */
struct ManBook
{
    int left;
    int top;
    int width;
    int height;
};

template <class T>
class Screen
{
    private:
        static int height, width;
        static SmartArray<T> buffer;
        static SmartArray<bool> allocated;
        static std::vector<ManBook> manBooks;
        
    public:
        Screen(int h, int w);
        ~Screen();
        
        Interface<T> &getInterface();
        NoticeBoard<T> &getNoticBoard(const Id &id);
};

template <class T>
int Screen<T>::height;

template <class T>
int Screen<T>::width;

template <class T>
SmartArray<T> Screen<T>::buffer;

template <class T>
SmartArray<bool> Screen<T>::allocated;

template <class T>
Screen<T>::Screen(int h, int w)
{
    height = h;
    width = w;
    
    buffer = createArray<T>(height, width);
    allocated = createArray<T>(height, width);
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            allocated[i][j] = false;
        }
    }
}

template <class T>
Screen<T>::~Screen() {}

class ScreenChar: public Screen<char>
{
    public:
        ScreenChar(int height, int width);
};

#endif
