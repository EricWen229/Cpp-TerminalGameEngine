#include "Dynamic.h"

int main()
{
    Object::RegisterInfo_S();
    Object *object =
        ClassInfos().getClassInfo("Object")
        -> getConstructor()(null, 0);
    object -> RegisterInfo_N();
    object -> getClassInfo_N().getDynamicFn("run")(null, 0);
}
