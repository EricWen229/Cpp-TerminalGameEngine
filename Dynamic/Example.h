#ifndef Example_H
#define Example_H

#include "ObjectDynamic.h"
#include <iostream>

/* example */
class Base: virtual public DynamicRootObject
{
        Declare_Object;
        
    public:
        Base();
        /* 如果非虚析构函数，会导致内存泄漏 */
        /* 可能是std:bind中类似于智能指针导致的问题 */
        virtual ~Base();
        
        virtual void sayHello(void *unused);
};

class Derived: public Base
{
        Declare_Object;
        
    public:
        Derived();
        virtual ~Derived();
        
        void sayHello(void *unusedP);
};

#endif
