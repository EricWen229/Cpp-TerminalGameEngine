#include "A.h"

Implement_Class(A)
{
    Register_Fn(A, sayHello);
}

A::A() {}

A::~A()
{
}

A *A::createObject(void **unusedP, int unusedI)
{
    return new A;
}

void *A::sayHello(void *unusedP, int unusedI)
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

Son *Son::createObject(void **unusedP, int unusedI)
{
    return new Son;
}

void *Son::sayHello(void *unusedP, int unusedI)
{
    std::cout << "Hi!" << std::endl;
    return null;
}
