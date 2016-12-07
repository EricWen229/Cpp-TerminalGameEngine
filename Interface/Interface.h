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
class Interface: virtual public DynamicRootObject
{
    public:
        Interface();
        virtual ~Interface();
        virtual void init(SmartArray<char> b, ObjectId sendTo) = 0;
        virtual void loop() = 0;
        virtual void end() = 0;
};

/* singleton */
class Ncurses: public Interface
{
        Declare_Object;
        
    private:
        static SmartArray<char> buffer;
        static Thread pid[2];
        static ObjectId sendTo;
        static bool exit;
        
        void *input(void *unused);
        void handleMessageUpdate(void *unused);
        
    public:
        Ncurses();
        virtual ~Ncurses();
        static Ncurses *createObject(void *unusedP);
        
        void init(SmartArray<char>b, ObjectId st);
        void loop();
        void end();
};

#endif
