#include "Dynamic.h"
#include <iostream>

class A: public Object
{
        Declare_Class;
    public:
        A();
        static Object *createObject(void **unusedP, int unusedI);
        void *sayHello(void **paras, int n);
};

Implement_Class(A)
{
    Register_Fn(A, sayHello);
}

A::A()
{
    std::cout << "Hi, I' A!" << std::endl;
}

Object *A::createObject(void **unusedP, int unusedI)
{
    return new A;
}

void *A::sayHello(void **paras, int n)
{
    std::cout << "Hello!" << std::endl;
    std::cout << n << std::endl;
    /* std::cout << *((int *)paras[0]) << std::endl; */
    return null;
}

int main()
{
    Object::RegisterInfo_S();
    A::RegisterInfo_S();
    /* Object *object = */
    /*     ClassInfos().getClassInfo("Object") */
    /*     -> getConstructor()(null, 0); */
    /* object -> RegisterInfo_N(); */
    /* int b[] = {2}; */
    /* object -> getClassInfo_N().getDynamicFn("run")((void **)b, 1); */
    Object *a =
        ClassInfos().getClassInfo("A")
        -> getConstructor()(null, 0);
    a -> RegisterInfo_N();
    int b[] = { 2 };
    ClassInfo_N::DynamicFn f = a -> getClassInfo_N().getDynamicFn("sayHello");
    f((void **)&b, 1);
}
