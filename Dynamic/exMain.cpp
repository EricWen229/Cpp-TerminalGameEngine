#include "Dynamic.h"
#include "Example.h"
#include <iostream>
#include <memory>

using std::dynamic_pointer_cast;

int main()
{
    int x = 1;
    int c = 'c';
    void *b[] = {(void *) &x, (void *) &c};
    
    Father::RegisterClassInfo();
    auto f =
        dynamic_pointer_cast<Father>
        (ClassInfos().getClassInfo("Father")
         -> Constructor(null));
    /* f -> RegisterObjectInfo(); */
    f -> getObjectInfo().getDynamicFn("sayHello")((void *)&b);
    
    Son::RegisterClassInfo();
    auto s =
        dynamic_pointer_cast<Father>
        (ClassInfos().getClassInfo("Son")
         -> Constructor(null));
    /* s -> RegisterObjectInfo(); */
    s -> getObjectInfo().getDynamicFn("sayHello")((void *)&b);
    
    /* Singleton::RegisterClassInfo(); */
    /* Singleton *sin = */
    /*     (Singleton *)ClassInfos().getClassInfo("Singleton") */
    /*     -> Constructor(null); */
    /* sin -> RegisterObjectInfo(); */
    /* sin -> getObjectInfo().getDynamicFn("sayHello")(null); */
    /* ObjectInfos().getObjectInfo(-1) -> getDynamicFn("sayHello")(null); */
    
    auto p = ObjectInfos().getObjectInfo(1);
    p -> getDynamicFn("sayHello")((void *)&b);
    
    auto q = ObjectInfos().getObjectInfo(2);
    q -> getDynamicFn("sayHello")(b);
    std::cout << GetObjectId()() << std::endl;
    std::cout << GetObjectId()() << std::endl;
    
    std::cout << f -> getClassInfo().ClassName << std::endl;
    std::cout << s -> getClassInfo().ClassName << std::endl;
    /* std::cout << sin -> getClassInfo().ClassName << std::endl; */
    
    /* delete f; */
    /* delete s; */
    /* delete sin; */
}
