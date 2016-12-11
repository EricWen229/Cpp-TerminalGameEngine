#include "Sprite.h"

bool operator>(const RSprite &a, const RSprite &b)
{
    return a.zIndex > b.zIndex;
}
