#ifndef Interface_H
#define Interface_H

#include "../Array/Array.h"
#include "../Dynamic/ObjectDynamic.h"
#include "../MailBox/MailBox.h"
#include "Sprite.h"
#include "PQueue.h"
#include <functional>
#include <ncurses.h>

template <class T>
class Interface: public DynamicRootObject
{
        Declare_Object;
        
    private:
        static bool firstInstance;
        static SmartArray<pQueue<RSprite> > spriteBitmap;
        virtual void update() = 0;
        
    protected:
        static SmartArray<bool> change;
        static SmartArray<T> buffer;
        
    public:
        Interface(SmartArray<T> b);
        virtual ~Interface();
        
        virtual void handleMessageSpriteApp(void *p);
        virtual void handleMessageSpriteDis(void *p);
};

template <class T>
Implement_Object(Interface<T>)
{
    Register_Object(Interface<T>);
    Register_Fn(Interface<T>, handleMessageSpriteApp);
    Register_Fn(Interface<T>, handleMessageSpriteDis);
}

template <class T>
bool Interface<T>::firstInstance = true;

template <class T>
SmartArray<pQueue<RSprite> > Interface<T>::spriteBitmap;

template <class T>
SmartArray<bool> Interface<T>::change;

template <class T>
SmartArray<T> Interface<T>::buffer;

template <class T>
Interface<T>::Interface(SmartArray<T> b):
    DynamicRootObject(-1)
{
    if (firstInstance)
    {
        buffer = b;
        
        int height = buffer -> height;
        int width = buffer -> width;
        
        spriteBitmap = createArray<pQueue<RSprite> >(height, width);
        
        change = createArray<bool>(height, width);
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                change[i][j] = false;
            }
        }
        
        RegisterObjectInfo();
        firstInstance = false;
    }
}

template <class T>
Interface<T>::~Interface()
{
    firstInstance = true;
}

template <class T>
void Interface<T>::handleMessageSpriteApp(void *p)
{
    Assert(p != nullptr);
    Message msg = *((Message *)p);
    ObjectId from = msg.from;
    
    Assert(ObjectInfos().getObjectInfo(from) != nullptr);
    Assert(ObjectInfos().getObjectInfo(from) -> getObject() != nullptr);
    Sprite<T> *sprite =
        dynamic_cast<Sprite<T> *>
        ((ObjectInfos().getObjectInfo(from) -> getObject()));
    Assert(sprite != nullptr);
    
    int height, width, zIndex;
    std::tie(height, width, zIndex) = sprite -> getPars();
    int startI, startJ;
    std::tie(startI, startJ) = sprite -> getPos();
    if (startI < 0)
    {
        sprite -> posI = 0;
        sprite -> ifBound(OutBoundTop);
    }
    else if (startI + height > buffer -> height)
    {
        sprite -> posI = buffer -> height - height;
        sprite -> ifBound(OutBoundBottom);
    }
    if (startJ < 0)
    {
        sprite -> posJ = 0;
        sprite -> ifBound(OutBoundLeft);
    }
    else if (startJ + width > buffer -> width)
    {
        sprite -> posJ = buffer -> width - width;
        sprite -> ifBound(OutBoundRight);
    }
    std::tie(startI, startJ) = sprite -> getPos();
    Assert(startI >= 0);
    Assert(startI + height <= buffer -> height);
    Assert(startJ >= 0);
    Assert(startJ + width <= buffer -> width);
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Assert
            (
                spriteBitmap[startI + i][startJ + j].
                exist(RSprite(from, zIndex)) == false
            );
            spriteBitmap[startI + i][startJ + j].
            push(RSprite(from, zIndex));
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Assert(spriteBitmap[startI + i][startJ + j].empty() == false);
            if (spriteBitmap[startI + i][startJ + j].top().objectId == from)
            {
                buffer[startI + i][startJ + j] = sprite -> getPixel(i, j);
                change[startI + i][startJ + j] = true;
            }
        }
    }
    
    bool needUpdate = (msg.description != "fasle");
    if (needUpdate)
    {
        update();
    }
}

template <class T>
void Interface<T>::handleMessageSpriteDis(void *p)
{
    Assert(p != nullptr);
    Message msg = *((Message *)p);
    ObjectId from = msg.from;
    
    Assert(ObjectInfos().getObjectInfo(from) != nullptr);
    Assert(ObjectInfos().getObjectInfo(from) -> getObject() != nullptr);
    Sprite<T> *sprite =
        dynamic_cast<Sprite<T> *>
        ((ObjectInfos().getObjectInfo(from) -> getObject()));
    Assert(sprite != nullptr);
    
    int height, width, zIndex;
    std::tie(height, width, zIndex) = sprite -> getPars();
    int startI, startJ;
    std::tie(startI, startJ) = sprite -> getPos();
    Assert(startI >= 0);
    Assert(startI + height <= buffer -> height);
    Assert(startJ >= 0);
    Assert(startJ + width <= buffer -> width);
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Assert
            (
                spriteBitmap[startI + i][startJ + j].
                exist(RSprite(from, zIndex)) == true
            );
            spriteBitmap[startI + i][startJ + j].
            erase(RSprite(from, zIndex));
            
            Assert
            (
                spriteBitmap[startI + i][startJ + j].empty() == false
            );
            ObjectId id =
                spriteBitmap[startI + i][startJ + j].
                top().objectId;
                
            Assert(ObjectInfos().getObjectInfo(id) != nullptr);
            Assert
            (
                ObjectInfos().getObjectInfo(id) -> getObject() != nullptr
            );
            Sprite<T> *sprite =
                dynamic_cast<Sprite<T> *>
                ((ObjectInfos().getObjectInfo(id) -> getObject()));
            Assert(sprite != nullptr);
            
            change[startI + i][startJ + j] = true;
            buffer[startI + i][startJ + j] = sprite -> getPixel(i, j);
        }
    }
    
    bool needUpdate = (msg.description != "fasle");
    if (needUpdate)
    {
        update();
    }
}

class Ncurses: public Interface<char>
{
    private:
        static Thread pid;
        static ObjectId sendTo;
        static bool begin;
        
        void *input(void *unused);
        void update();
        
    public:
        Ncurses(SmartArray<char> b, ObjectId st);
        virtual ~Ncurses();
        
        void end();
};

#endif
