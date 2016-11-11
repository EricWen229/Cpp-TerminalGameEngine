#ifndef Screen_H
#define Screen_H

#include "Array.h"
#include <iostream>

#define null nullptr

class Show
{
    private:
        SmartArray<char> buffer;
        
    public:
        Show(SmartArray<char> b);
        ~Show();
        virtual void init() = 0;
        virtual void erase(int i, int j) = 0;
        virtual void write(int i, int j, char c) = 0;
};

class Screen
{
    private:
        Show *show;
        SmartArray<char> lastBuffer;
        SmartArray<char> buffer;
        int width, height;
        
    public:
        Screen(int w, int h, Show *s);
        ~Screen();
        void print();
};

#endif
