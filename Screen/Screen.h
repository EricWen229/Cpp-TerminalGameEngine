#ifndef Screen_H
#define Screen_H

#include "../Array/Array.h"
#include "../Interface/Interface.h"
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

/* singleton */
class Screen
{
    private:
        static Interface *interface;
        static SmartArray<char> buffer;
        static int width, height;
        static std::vector<ManBook> books;
        static Interface::HandleFunc handleFunc;
        
    public:
        /* dependency injection */
        Screen(int w, int h, Interface *i, Interface::HandleFunc hf);
        ~Screen();
        
        Id alloc(int top, int left, int height, int width);
        SmartArray<char> get(Id id);
        /* void free(Id id); */
        void run();
};

#endif
