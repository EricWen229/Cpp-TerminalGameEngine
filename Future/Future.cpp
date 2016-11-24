#include "Future.h"

Id getId::id = 0;

Id getId::operator()()
{
    id++;
    return id;
}

void Future::begin()
{
    std::function<void *(void *)> loop = [&](void *unused)
    {
        /* 需要临界区 */
        fnResourse.P();
        AsyncFnType fn;
        ParasType paras;
        std::tie(fn, paras, std::ignore, std::ignore, std::ignore) =
            container[active.front()];
        std::get<2>(container[active.front()]) = fn(paras);
        std::get<4>(container[active.front()]) = true;
        active.pop_front();
        return nullptr;
    };
    thread = createPthread(loop);
}

void Future::end()
{
    waitPthread(thread);
}

Id Future::putAsyncFn(AsyncFnType fn)
{
    Id id = getId()();
    /* inactive.push_back(id); */
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
        active.push_back(id);
        fnResourse.V();
        return true;
    }
}

bool Future::isReady(Id id)
{
    return std::get<4>(container[id]);
}

void Future::wait(Id id)
{
    mutex.P();
    for (std::list<Id>::const_iterator it = active.begin();
            it != active.end(); it++)
    {
        if (*it == id)
        {
            active.erase(it);
            break;
        }
    }
    mutex.V();
    fnResourse.P();
    AsyncFnType fn;
    ParasType paras;
    std::tie(fn, paras, std::ignore, std::ignore, std::ignore) =
        container[active.front()];
    std::get<2>(container[id]) = fn(paras);
    std::get<4>(container[id]) = true;
}

void *Future::getResult(Id id)
{
    return std::get<2>(container[id]);
}
