#ifndef NoticeBoard_H
#define NoticeBoard_H

#include "../Array/Array.h"
#include "../DiagHelper.h"
#include <ncurses.h>

template <class T>
class NoticeBoard
{
    protected:
        SmartArray<T> buffer;
        SmartArray<bool> change;
        const int offsetI, offsetJ;
        
    public:
        NoticeBoard(SmartArray<T> b, int i = 0, int j = 0);
        virtual ~NoticeBoard();
        
        T &at(int i, int j);
        virtual void update() = 0;
};

template <class T>
NoticeBoard<T>::NoticeBoard(SmartArray<T> b, int i, int j):
    buffer(b), offsetI(i), offsetJ(j)
{
    int height = buffer -> height;
    int width = buffer -> width;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            change[i][j] = false;
        }
    }
}

template <class T>
NoticeBoard<T>::~NoticeBoard() {}

template <class T>
T &NoticeBoard<T>::at(int i, int j)
{
    Assert(i >= 0 && i < buffer -> height);
    Assert(j >= 0 && j < buffer -> width);
    return buffer[i][j];
}

class NcursesBoard: public NoticeBoard<char>
{
    public:
        void update();
};

#endif
