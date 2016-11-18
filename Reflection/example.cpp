#include "Dynamic.h"
#include "A.h"
#include <iostream>

int main()
{
    A::RegisterInfo_S();
    A *a =
        (A *)ClassInfos().getClassInfo("A")
        -> getConstructor()(null, 0);
    a -> RegisterInfo_N();
    int b[] = { 2 };
    ClassInfo_N::DynamicFn f = a -> getClassInfo_N().getDynamicFn("sayHello");
    f((void **)&b, 1);
    /* f(null, 1); */
}
