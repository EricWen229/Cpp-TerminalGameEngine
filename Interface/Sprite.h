#ifndef Sprite_H
#define Sprite_H

#include "../Dynamic/ObjectDynamic.h"

class Sprite: virtual public DynamicRootObject
{
    private:
        int posI, posJ, height, width;
        /* zIndex代表Sprite在屏幕上显示的优先级 */
        int zIndex;
        
    public:
        Sprite(int i, int j, int height, int width, int zIndex = 1);
        ~Sprite();
};

#endif
