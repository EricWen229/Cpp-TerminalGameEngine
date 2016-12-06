#include "Example.h"

Implement_Object(Base)
{
    Register_Object(Base);
    Register_Fn(Base, sayHello);
}

Base::Base(): DynamicRootObject()
{
    RegisterObjectInfo();
}
Base::~Base() {}

void Base::sayHello(void *unused)
{
    std::cout << "Hello!" << std::endl;
    std::cout << "I'm Base." << std::endl;
}

Implement_Object(Derived)
{
    Register_Object(Derived);
    Register_Fn(Derived, sayHello);
}

Derived::Derived(): Base()
{
    RegisterObjectInfo();
}
Derived::~Derived() {}

void Derived::sayHello(void *unused)
{
    if (unused == nullptr)
    {
        std::cout << "Hi!" << std::endl;
        std::cout << "I' m Derived." << std::endl;
    }
    else
    {
        void **p = (void **)unused;
        int a = *((int *)p[0]);
        char b = *((char *)p[1]);
        std::cout << a << " " << b << std::endl;
    }
}
