#include "Sprite/Sprite.h"

bool operator>(const RSprite &a, const RSprite &b)
{
    return a.zIndex > b.zIndex;
}

bool operator==(const RSprite &a, const RSprite &b)
{
    return a.objectId == b.objectId;
}

RSprite::RSprite(ObjectId id, int z):
    objectId(id), zIndex(z) {}
