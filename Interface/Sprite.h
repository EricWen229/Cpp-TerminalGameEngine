#ifndef Sprite_H
#define Sprite_H

#include "../Dynamic/ObjectDynamic.h"
#include "../Array/Array.h"
#include <tuple>

template <class T>
class Sprite: virtual public DynamicRootObject
{
    private:
        int posI, posJ, height, width;
        /* zIndex代表Sprite在屏幕上显示的优先级 */
        int zIndex;
        SmartArray<T> appear;
        
    public:
        Sprite(int i, int j, int height, int width, int zIndex = 1);
        ~Sprite();
        
        std::tuple<int, int> getPos();
        std::tuple<int, int, int> getPars();
        T getPixel(int i, int j);
        
        void moveTo(int newI, int newJ);
        void moveAdd(int deltaI, int deltaJ);
};

class RSprite
{
    public:
        ObjectId objectId;
        int zIndex;
        RSprite(ObjectId id, int z);
};

bool operator>(const RSprite &a, const RSprite &b)
{
    return a.zIndex > b.zIndex;
}

#endif
