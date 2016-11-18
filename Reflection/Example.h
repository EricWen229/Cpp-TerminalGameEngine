#ifndef Example_H
#define Example_H

#include "Dynamic.h"

/* example */
class Father
{
        Declare_Class;
    public:
        Father();
        ~Father();
        
        static Father *createObject(void **unusedP, int unusedI);
        
        virtual void *sayHello(void *unusedP, int unusedI);
};

class Son: public Father
{
        Declare_Class;
    public:
        Son();
        ~Son();
        
        static Son *createObject(void **unusedP, int unusedI);
        void *sayHello(void *unusedP, int unusedI);
};

#endif
