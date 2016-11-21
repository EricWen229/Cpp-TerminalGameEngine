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

Father *Father::createObject(void **unusedP, int unusedI)
{
    return new Father;
}

void *Father::sayHello(void *unusedP, int unusedI)
{
    std::cout << "Hello!" << std::endl;
    std::cout << unusedI << std::endl;
    std::cout << ((int *)unusedP)[0] << std::endl;
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

Son *Son::createObject(void **unusedP, int unusedI)
{
    return new Son;
}

void *Son::sayHello(void *unusedP, int unusedI)
{
    std::cout << "Hi!" << std::endl;
    return null;
}
