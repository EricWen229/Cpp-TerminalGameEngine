#include "Dynamic.h"

int main()
{
    Object *object =
        ClassInfos().getClass("Object")
        -> getConstructor()(null, 0);
    object -> init();
    ClassInfos().getClass("Object") -> getDynamicFn("run")(null, 0);
}
