#ifndef A_H
#define A_H

#include "Dynamic.h"

/* example */
class A
{
        Declare_Class;
    public:
        A();
        ~A();
        
        static A *createObject(void **unusedP, int unusedI);
        
        void *sayHello(void **unusedP, int unusedI);
};

#endif
