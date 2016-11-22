#ifndef Screen_H
#define Screen_H

#include "../Array/Array.h"
#include "../Interface/Interface.h"
#include "../Semaphore/Semaphore.h"
#include <vector>
#include <functional>

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
        static int height, width;
        static SmartArray<char> buffer;
        static Interface *interface;
        static Interface::HandleFunc handleFunc;
        
        static std::vector<ManBook> books;
        static Thread pid;
        
        static void *runHelper(void *unused);
        
    public:
        void init(
            int h, int w,
            Interface::HandleFunc hf);
        void begin();
        void end();
        
        Id alloc(int top, int left, int height, int width);
        SmartArray<char> get(Id id);
        void free(Id id);
        
        bool isExit();
        void clean();
};

#endif
