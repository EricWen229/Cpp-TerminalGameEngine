#ifndef Example_H
#define Example_H

#include "Dynamic.h"

/* example */
class Father
{
        Declare_Class;
    public:
        Father();
        /* 如果非虚析构函数，会导致内存泄漏 */
        /* 可能是std:bind中类似于智能指针导致的问题 */
        virtual ~Father();
        
        static Father *createObject(void *unusedP);
        
        virtual void *sayHello(void *unusedP);
};

class Son: public Father
{
        Declare_Class;
    public:
        Son();
        virtual ~Son();
        
        static Son *createObject(void *unusedP);
        void *sayHello(void *unusedP);
};

#endif
