#include "Dynamic.h"
#include "Example.h"
#include <iostream>

int main()
{
    int b[] = { 2 };
    
    Father::RegisterClassInfo();
    Father *f =
        (Father *)ClassInfos().getClassInfo("Father")
        -> getConstructor()(null, 0);
    f -> RegisterObjectInfo();
    f -> getObjectInfo().getDynamicFn("sayHello")((void **)&b, 1);
    
    Son::RegisterClassInfo();
    Father *s =
        (Son *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null, 0);
    s -> RegisterObjectInfo();
    s -> getObjectInfo().getDynamicFn("sayHello")((void **)&b, 1);
    
    delete f;
    delete s;
}
