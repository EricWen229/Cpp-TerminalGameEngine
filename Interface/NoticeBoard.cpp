#include "NoticeBoard.h"

void NcursesBoard::update()
{
    for (int i = 0; i < buffer -> height; i++)
    {
        for (int j = 0; j < buffer -> width; j++)
        {
            if (change[i][j])
            {
                mvaddch(offsetI + i, offsetJ + j, buffer[i][j]);
                change[i][j] = false;
            }
        }
    }
    refresh();
}
