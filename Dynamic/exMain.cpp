#include "Dynamic.h"
#include "Example.h"
#include <iostream>

int main()
{
    int x = 1;
    int c = 'c';
    void *b[] = {(void *) &x, (void *) &c};
    
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
    
    Singleton::RegisterClassInfo();
    Singleton *sin =
        (Singleton *)ClassInfos().getClassInfo("Singleton")
        -> getConstructor()(null);
    sin -> RegisterObjectInfo();
    sin -> getObjectInfo().getDynamicFn("sayHello")(null);
    ObjectInfos().getObjectInfo(-1) -> getDynamicFn("sayHello")(null);
    
    auto p = ObjectInfos().getObjectInfo(1);
    p -> getDynamicFn("sayHello")((void *)&b);
    
    auto q = ObjectInfos().getObjectInfo(2);
    q -> getDynamicFn("sayHello")(b);
    std::cout << GetObjectId()() << std::endl;
    std::cout << GetObjectId()() << std::endl;
    
    std::cout << f -> getClassInfo().getName() << std::endl;
    std::cout << s -> getClassInfo().getName() << std::endl;
    std::cout << sin -> getClassInfo().getName() << std::endl;
    
    delete f;
    delete s;
    delete sin;
}
