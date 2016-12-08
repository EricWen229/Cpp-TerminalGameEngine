#ifndef Interface_H
#define Interface_H

#include "../Array/Array.h"
#include "../Dynamic/ObjectDynamic.h"
#include "../MailBox/MailBox.h"
#include <functional>
#include <ncurses.h>

#define InterfaceId -1
/* user interface */
/* interact with user */
class Interface
{
    public:
        Interface();
        virtual ~Interface();
};

/* singleton */
class Ncurses: public Interface, virtual public DynamicRootObject
{
        Declare_Object;
        
    private:
        static SmartArray<char> buffer;
        static Thread pid;
        static ObjectId sendTo;
        static bool begin;
        
        void *input(void *unused);
        virtual void handleMessageUpdate(void *unused);
        
    public:
        Ncurses(SmartArray<char> b, ObjectId st);
        virtual ~Ncurses();
        
        /* void init(SmartArray<char>b, ObjectId st); */
        /* void loop(); */
        void end();
};

#endif
