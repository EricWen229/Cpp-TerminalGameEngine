#include "Example.h"

Implement_Class(Father)
{
    Register_Object(Father);
    Register_Fn(Father, sayHello);
}

Father::Father(): objectId(GetObjectId()()) {}

Father::~Father()
{
    Out_Object(Father);
}

Father *Father::createObject(void *unusedP)
{
    return new Father;
}

void *Father::sayHello(void *unusedP)
{
    std::cout << "Hello!" << std::endl;
    /* std::cout << ((int *)unusedP)[0] << std::endl; */
    return null;
}

Implement_Class(Son)
{
    Register_Object(Son);
    Register_Fn(Son, sayHello);
}

Son::Son(): objectId(GetObjectId()()) {}

Son::~Son()
{
    Out_Object(Son);
}

Son *Son::createObject(void *unusedP)
{
    return new Son;
}

void *Son::sayHello(void *unusedP)
{
    if (unusedP == null)
    {
        std::cout << "Hi!" << std::endl;
    }
    else
    {
        void **p = (void **)unusedP;
        int a = *((int *)p[0]);
        char b = *((char *)p[1]);
        std::cout << a << " " << b << std::endl;
    }
    return null;
}
