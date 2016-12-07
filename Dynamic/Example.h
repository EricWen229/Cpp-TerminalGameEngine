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
        
        /* 如果子类有同名函数，建议声明为virtual */
        /* 进一步地，如果不确定子类是否会有同名函数，建议声明为virtual */
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

/* 本次开发Singleton指的都是数据静态，方法不静态的类 */

#endif
