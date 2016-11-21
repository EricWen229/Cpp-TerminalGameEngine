#include "Dynamic.h"
#include "Example.h"
#include <iostream>

int main()
{
    int b[] = { 2 };
    
    Father::RegisterClassInfo();
    Father *f =
        (Father *)ClassInfos().getClassInfo("Father")
        -> getConstructor()(null);
    f -> RegisterObjectInfo();
    f -> getObjectInfo().getDynamicFn("sayHello")((void *)&b);
    
    Son::RegisterClassInfo();
    Father *s =
        (Son *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null);
    s -> RegisterObjectInfo();
    s -> getObjectInfo().getDynamicFn("sayHello")((void *)&b);
    
    auto p = ObjectInfos().getObjectInfo(1);
    p -> getDynamicFn("sayHello")((void *)&b);
    
    delete f;
    delete s;
}
