#include "Example.h"

Implement_Class(Father)
{
    Register_Fn(Father, sayHello);
}

Father::Father() {}

Father::~Father() {}

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
    Register_Fn(Son, sayHello);
}

Son::Son() {}

Son::~Son() {}

Son *Son::createObject(void **unusedP, int unusedI)
{
    return new Son;
}

void *Son::sayHello(void *unusedP, int unusedI)
{
    std::cout << "Hi!" << std::endl;
    return null;
}
