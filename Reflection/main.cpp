#include "Dynamic.h"

int main()
{
    ClassInfos().regClass("Object", &Object::classInfo_s);
    Object *object =
        ClassInfos().getClassInfo("Object")
        -> getConstructor()(null, 0);
    object -> RegisterInfos();
    object -> getClassInfo_N().getDynamicFn("run")(null, 0);
}
