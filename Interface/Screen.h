#ifndef Screen_H
#define Screen_H

#include "../Array/Array.h"
#include <ncurses.h>

template <class T>
class Screen
{
    private:
        static int height, width;
        static bool firstInstance;
        static SmartArray<T> buffer;
        static SmartArray<bool> allocated;
        
    public:
        Screen(int h, int w);
        ~Screen();
};

template <class T>
int Screen<T>::height;

template <class T>
int Screen<T>::width;

template <class T>
bool Screen<T>::firstInstance = true;

template <class T>
SmartArray<T> Screen<T>::buffer;

template <class T>
SmartArray<bool> Screen<T>::allocated;

template <class T>
Screen<T>::Screen(int h, int w)
{
    if (firstInstance)
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
        
        firstInstance = false;
    }
}

template <class T>
Screen<T>::~Screen()
{
    firstInstance = true;
}

class ScreenChar: public Screen<char>
{
    public:
        ScreenChar(int height, int width);
};

#endif
