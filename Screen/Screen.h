#ifndef Screen_H
#define Screen_H

#include "../Array/Array.h"
#include "../Interface/Interface.h"
#include "../MailBox/MailBox.h"
#include "../Semaphore/Semaphore.h"
#include "../Dynamic/Dynamic.h"
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
        Declare_Class;
    private:
        static ObjectId objectId;
        static int height, width;
        static SmartArray<char> buffer;
        static Interface &interface;
        static ObjectId sendTo;
        static std::vector<ManBook> books;
        
    public:
        Screen();
        virtual ~Screen();
        static Screen *createObject(void *unusedP);
        
        void init(int h, int w, ObjectId st);
        void end();
        
        void *handleMessageUpdate(void *unusedP);
        void *handleMessageKeyDown(void *unusedP);
        
        Id alloc(int top, int left, int height, int width);
        SmartArray<char> get(Id id);
        void free(Id id);
        
        bool isExit();
};

#endif
