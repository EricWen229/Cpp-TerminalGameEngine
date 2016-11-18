#include "Dynamic.h"
#include "Example.h"
#include <iostream>

int main()
{
    int b[] = { 2 };
    
    Father::RegisterInfo_S();
    Father *f =
        (Father *)ClassInfos().getClassInfo("Father")
        -> getConstructor()(null, 0);
    f -> RegisterInfo_N();
    f -> getClassInfo_N().getDynamicFn("sayHello")((void **)&b, 1);
    
    Son::RegisterInfo_S();
    Father *s =
        (Son *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null, 0);
    s -> RegisterInfo_N();
    s -> getClassInfo_N().getDynamicFn("sayHello")((void **)&b, 1);
    
    delete f;
    delete s;
}
