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

void *A::sayHello(void **unusedP, int unusedI)
{
    std::cout << "Hello!" << std::endl;
    std::cout << unusedI << std::endl;
    return null;
}
