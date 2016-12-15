#include "PQueue.h"
#include "Sprite.h"

bool PQueue::empty() const
{
    return container.empty();
}

const ObjectId PQueue::top() const
{
    return container.front();
}

void PQueue::pop()
{
    container.erase(container.begin());
}

void PQueue::push(const ObjectId id)
{
    for
    (
        std::list<ObjectId>::const_iterator it = container.begin();
        it != container.end();
        it++
    )
    {
        Assert(ObjectInfos().getObjectInfo(from) != nullptr);
        Assert(ObjectInfos().getObjectInfo(from) -> getObject() != nullptr);
        Sprite<T> *sprite =
            dynamic_cast<Sprite<T> *>
            ((ObjectInfos().getObjectInfo(from) -> getObject()));
        Assert(sprite != nullptr);
    }
}
