#ifndef Screen_H
#define Screen_H

#include "Array.h"
#include <iostream>
#include <vector>

#define null nullptr

class Interface
{
    public:
        Interface(SmartArray<char> b);
        ~Interface();
        virtual void init() = 0;
        virtual void erase(int i, int j) = 0;
        virtual void write(int i, int j, char c) = 0;
};

struct manageBook
{
    int left;
    int top;
    int width;
    int height;
};

class Screen
{
    private:
        Interface *show;
        SmartArray<char> buffer;
        int width, height;
        std::vector<manageBook> books;
        
    public:
        Screen(int w, int h, Interface *s);
        ~Screen();
        
        int alloc(int left, int right, int width, int height);
        int get();
        int free(int id);
        void print();
};

#endif
