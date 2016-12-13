#include "Sprite.h"

bool operator>(const RSprite &a, const RSprite &b)
{
    return a.zIndex > b.zIndex;
}

bool operator==(const RSprite &a, const RSprite &b)
{
    return a.objectId == b.objectId;
}

RSprite::RSprite(ObjectId id, int z, int i, int j):
    objectId(id), zIndex(z), posI(i), posJ(j) {}
