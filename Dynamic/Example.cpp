#include "Example.h"

Implement_Class(Father);

Implement_Object(Father)
{
    Register_Object(Father);
    Register_Fn(Father, sayHello);
}

Father::Father(): DynamicRootObject()
{
    RegisterClassInfo();
    RegisterObjectInfo();
}

Father::~Father()
{
    Out_Object(Father);
}

unique_ptr<Father> Father::createObject(void *unused)
{
    return unique_ptr<Father>(new Father);
}

void *Father::sayHello(void *unused)
{
    std::cout << "Hello!" << std::endl;
    return null;
}

Implement_Class(Son);

Implement_Object(Son)
{
    Register_Object(Son);
    Register_Fn(Son, sayHello);
}

Son::Son(): Father()
{
    RegisterClassInfo();
    RegisterObjectInfo();
}

Son::~Son()
{
    Out_Object(Son);
}

unique_ptr<Son> Son::createObject(void *unused)
{
    return unique_ptr<Son>(new Son);
}

void *Son::sayHello(void *unused)
{
    if (unused == null)
    {
        std::cout << "Hi!" << std::endl;
    }
    else
    {
        void **p = (void **)unused;
        int a = *((int *)p[0]);
        char b = *((char *)p[1]);
        std::cout << a << " " << b << std::endl;
    }
    return null;
}

ObjectId Singleton::objectId = -1;
