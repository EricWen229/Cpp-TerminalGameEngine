#ifndef Sprite_H
#define Sprite_H

#include "../Dynamic/ObjectDynamic.h"
#include "../Array/Array.h"
#include "../MailBox/MailBox.h"
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
        Sprite(int i, int j, int h, int w, int z = 1);
        ~Sprite();
        
        std::tuple<int, int> getPos();
        std::tuple<int, int, int> getPars();
        T getPixel(int i, int j);
        
        void moveTo(int newI, int newJ);
        void moveAdd(int deltaI, int deltaJ);
};

template <class T>
Sprite<T>::Sprite(int i, int j, int h,int w, int z):
    posI(i), posJ(j),
    height(h), width(w),
    zIndex(z)
{}

template <class T>
Sprite<T>::~Sprite() {}

template <class T>
std::tuple<int, int> Sprite<T>::getPos()
{
    return std::tuple<int, int>(posI, posJ);
}

template <class T>
std::tuple<int, int, int> Sprite<T>::getPars()
{
    return std::tuple<int, int, int>(height, width, zIndex);
}

template <class T>
T Sprite<T>::getPixel(int i, int j)
{
    Assert(0 <= i && i <= height);
    Assert(0 <= j && j <= width);
    return appear[i][j];
}

template <class T>
void Sprite<T>::moveTo(int newI, int newJ)
{
    if (posI == newI && posJ == newJ)
    {
        return;
    }
    
    MailBox().put
    (Message
     (
         objectId, -1, "SpriteDis",
         std::to_string(posI) + std::string(" ") + std::to_string(posJ)
     )
    );
    posI = newI;
    posJ = newJ;
    MailBox().put
    (Message
     (
         objectId, -1, "SpriteApp",
         std::to_string(posI) + std::string(" ") + std::to_string(posJ)
     )
    );
}

template <class T>
void Sprite<T>::moveAdd(int deltaI, int deltaJ)
{
    moveTo(posI + deltaI, posJ + deltaJ);
}

class RSprite
{
    public:
        ObjectId objectId;
        int zIndex;
        RSprite(ObjectId id, int z);
};

bool operator>(const RSprite &a, const RSprite &b);

#endif
