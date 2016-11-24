#include "Future.h"

Id Future::putAsyncFn(AsyncFnType fn)
{
    Id id = getId()();
    container.insert
    (ContainerType::value_type
     (id, EleType(fn, nullptr, nullptr, false, false)));
    return id;
}

bool Future::putParas(Id id, void *paras)
{
    if (std::get<3>(container[id]) == true)
    {
        return false;
    }
    else
    {
        std::get<1>(container[id]) = paras;
        std::get<3>(container[id]) = true;
        return true;
    }
}

bool Future::isReady(Id id)
{
    return std::get<4>(container[id]);
}

void *Future::getResult(Id id)
{
    return std::get<2>(container[id]);
}
