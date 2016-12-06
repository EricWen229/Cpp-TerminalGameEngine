#include "ObjectDynamic.h"
#include "Example.h"
#include <iostream>

int main()
{
    Base base;
    Derived derived;
    ObjectInfos().getObjectInfo(base.objectId)
    -> getDynamicFn("sayHello")(nullptr);
    ObjectInfos().getObjectInfo(derived.objectId)
    -> getDynamicFn("sayHello")(nullptr);
}
