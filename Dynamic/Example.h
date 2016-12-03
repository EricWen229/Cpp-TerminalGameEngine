#ifndef Example_H
#define Example_H

#include "Dynamic.h"

/* example */
class Father: virtual public DynamicRootObject
{
        Declare_Class;
        Declare_Object;
    public:
        Father();
        /* 如果非虚析构函数，会导致内存泄漏 */
        /* 可能是std:bind中类似于智能指针导致的问题 */
        virtual ~Father();
        
        static Father *createObject(void *unused);
        
        virtual void *sayHello(void *unused);
};

class Son: public Father
{
        Declare_Class;
        Declare_Object;
    public:
        Son();
        virtual ~Son();
        
        static Son *createObject(void *unusedP);
        void *sayHello(void *unusedP);
};

class Singleton: public DynamicRootObject
{
        Declare_Class;
        Declare_Object;
    private:
        static ObjectId objectId;
        
    public:
        Singleton();
        virtual ~Singleton();
        static Singleton *createObject(void *unusedP);
        
        void *sayHello(void *unusedP);
};

#endif
