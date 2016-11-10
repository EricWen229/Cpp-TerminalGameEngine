#ifndef Screen_H
#define Screen_H

#include "Array.h"

#define null nullptr

class Screen
{
    private:
        SmartArray<char> lastBuffer;
        SmartArray<char> buffer;
        int width, height;
        
    public:
        Screen(int w, int h);
        ~Screen();
        void print();
};

#endif
