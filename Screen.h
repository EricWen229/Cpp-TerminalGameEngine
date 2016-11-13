#ifndef Screen_H
#define Screen_H

#include "Array/Array.h"
#include <iostream>
#include <vector>

#define null nullptr

typedef int Id;

/* manage book */
struct ManBook
{
    int left;
    int top;
    int width;
    int height;
};

class Screen
{
    private:
        Interface *interface;
        SmartArray<char> buffer;
        int width, height;
        std::vector<ManBook> books;
        
    public:
        Screen(int w, int h, Interface *i);
        ~Screen();
        
        Id alloc(int left, int right, int width, int height);
        SmartArray<char> get(Id id);
        void free(bool id);
        void print();
};

#endif
