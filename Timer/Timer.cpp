#include "Timer.h"

void *Timer::loopHelper(void *unused)
{
    count++;
    for (Container::const_iterator it = container.begin();
            it != container.end(); it++)
    {
        if (count % (it -> first) == 0)
        {
            ObjectId objectId;
            std::string funcName;
            void *paras;
            std::tie(objectId, funcName, paras) = it -> second;
            ObjectInfos().getObjectInfo(objectId)
            -> getDynamicFn(funcName)(paras);
        }
    }
    return null;
}

void Timer::reg
(ObjectId id,
 std::string funcName,
 void *paras,
 int frequency)
{
    container.insert(Container::value_type
                     (frequency,
                      Element(id, funcName, paras)));
}

void Timer::out(ObjectId id, std::string funcName)
{
    for (Container::const_iterator it = container.begin();
            it != container.end(); it++)
    {
        ObjectId objectId;
        std::string fN;
        std::tie(objectId, fN, std::ignore) = it -> second;
        if (objectId == id && fN == funcName)
        {
            container.erase(it);
            break;
        }
    }
}
