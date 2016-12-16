#ifndef Controller_H
#define Controller_H

#include "../Array/Array.h"
#include "../Interface/Interface.h"
#include "../Interface/Sprite.h"
#include <vector>
#include <functional>

/* 用反射代替ObjectType的判断 */
/* object.getClasInfo().getName() */

enum OutBoundType
{
    OutBoundTop,
    OutBoundBottom,
    OutBoundLeft,
    OutBoundRight
};

class Controller;
class Sprite
{
    private:
        friend class Controller;
        
    protected:
        int height, width;
        SmartArray<char> look;
        int i, j;
        
    public:
        Sprite();
        virtual ~Sprite();
        
        void moveTo(int newI, int newJ);
        void moveAdd(int deltaI, int deltaJ);
        
        virtual void ifBound(OutBoundType ot) = 0;
        virtual void ifBang(Sprite *thing) = 0;
        virtual bool live() = 0;
};

class UserSprite: public Sprite
{
    public:
        UserSprite();
        virtual ~UserSprite();
        void *handleMessageKeyDown(void *pointer);
};

class AutoSprite: public Sprite
{
    public:
        virtual ~AutoSprite();
        AutoSprite();
        virtual void handle() = 0;
};

/* singleton */
class Controller
{
    private:
        static UserSprite *user;
        static SmartArray<char> gameBuffer;
        
        static int height, width;
        static Screen screen;
        static std::vector<int> ids;
        
    public:
        void bound(Sprite *a);
        bool bangHelper(Sprite *a, Sprite *b);
        void bang();
        void clean();
        
    public:
        void init(int h, int w);
        void loop();
};

#endif
