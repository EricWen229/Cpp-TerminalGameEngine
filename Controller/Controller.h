#ifndef Controller_H
#define Controller_H

#include "../Array/Array.h"
#include "../Screen/Screen.h"
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
class AutoControlSprite;
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

class UserControlSprite: public Sprite
{
    public:
        UserControlSprite();
        virtual ~UserControlSprite();
        void *handleMessageKeyDown(void *pointer);
};

class AutoControlSprite: public Sprite
{
    public:
        virtual ~AutoControlSprite();
        AutoControlSprite();
        virtual void handle() = 0;
};

/* singleton */
class Controller
{
    public:
        typedef AutoControlSprite *(*Producer)();
        
    private:
        static UserControlSprite *users;
        static SmartArray<char> gameBuffer;
        
        static int height, width;
        static Screen screen;
        static std::vector<int> ids;
        
        static void boundHelper(Sprite *a);
        bool bangHelper(Sprite *a, Sprite *b);
        void bang();
        void clean();
        void produce();
        void shoot();
        void handle();
        void draw();
        
    public:
        virtual void init
        (int h, int w,
         UserControlSprite *u,
         Producer ps[], int nProducer);
        void loop();
};

#endif
