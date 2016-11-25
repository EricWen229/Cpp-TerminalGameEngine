#include "Future.h"

Id getId::id = 0;

Id getId::operator()()
{
    id++;
    return id;
}

Future::Future(): mutex(1) {}

void Future::begin()
{
    std::function<void *(void *)> loop = [&](void *unused)
    {
        while (!isExit)
        {
            fnResourse.P();
            mutex.P();
            assert(active.size() > 0);
            std::set<Id>::const_iterator it = active.begin();
            Id id = *it;
            active.erase(it);
            mutex.V();
            AsyncFnType fn;
            ParasType paras;
            assert(container.find(id) != container.end());
            std::tie(fn, paras, std::ignore, std::ignore, std::ignore) =
                container[id];
            std::get<2>(container[id]) = fn(paras);
            std::get<4>(container[id]) = true;
        }
        return nullptr;
    };
    thread = createPthread(loop);
}

void Future::end()
{
    isExit = true;
    putParas(putAsyncFn([](void *unused)
    {
        return nullptr;
    }), nullptr);
    waitPthread(thread);
}

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
    assert(container.find(id) != container.end());
    if (std::get<3>(container[id]) == true)
    {
        return false;
    }
    else
    {
        std::get<1>(container[id]) = paras;
        std::get<3>(container[id]) = true;
        assert(active.find(id) == active.end());
        active.insert(id);
        assert(active.find(id) != active.end());
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
    std::set<Id>::const_iterator it = active.find(id);
    if (it == active.end() || active.size() <= 1)
    {
        mutex.V();
        while (!isReady(id)) ;
        return;
    }
    active.erase(it);
    mutex.V();
    fnResourse.P();
    AsyncFnType fn;
    ParasType paras;
    std::tie(fn, paras, std::ignore, std::ignore, std::ignore) =
        container[id];
    std::get<2>(container[id]) = fn(paras);
    std::get<4>(container[id]) = true;
}

void *Future::getResult(Id id)
{
    return std::get<2>(container[id]);
}
