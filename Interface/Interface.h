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
class Interface
{
    private:
        static SmartArray<pQueue<RSprite> > spriteBitmap;
        virtual void update() = 0;
        
    protected:
        static SmartArray<bool> change;
        static SmartArray<T> buffer;
        
    public:
        Interface(SmartArray<T> b);
        virtual ~Interface();
        
        virtual void handleMessageUpdate(void *p);
        void handleMessageSpriteApp(void *p);
        void handleMessageSpriteDis(void *p);
};

template <class T>
SmartArray<pQueue<RSprite> > Interface<T>::spriteBitmap;

template <class T>
SmartArray<bool> Interface<T>::change;

template <class T>
SmartArray<T> Interface<T>::buffer;

template <class T>
Interface<T>::Interface(SmartArray<T> b)
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
}

template <class T>
Interface<T>::~Interface() {}

template <class T>
void Interface<T>::handleMessageSpriteApp(void *p)
{
    Message msg = *((Message *)p);
    ObjectId from = msg.from;
    
    Sprite<T> *sprite = dynamic_cast<Sprite<T> *>((ObjectInfos().getObjectInfo(from) -> getObject()));
    int height, width, zIndex;
    std::tie(height, width, zIndex) = sprite -> getPars();
    int startI, startJ;
    std::tie(startI, startJ) = sprite -> getPos();
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            spriteBitmap[startI + i][startJ + j].push(RSprite(from, zIndex, i, j));
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /* if (spriteBitmap[startI + i][startJ + j].top().objectId == from) */
            /* { */
            /*     update(startI + i, startJ + j, sprite -> getPixel(i, j)); */
            /* } */
            if (spriteBitmap[startI + i][startJ + j].top().objectId == from)
            {
                buffer[startI + i][startJ + j] = sprite -> getPixel(i, j);
                change[startI + i][startJ + j] = true;
                update();
            }
        }
    }
}

template <class T>
void Interface<T>::handleMessageSpriteDis(void *p)
{
    Message msg = *((Message *)p);
    ObjectId from = msg.from;
    
    Sprite<T> *sprite = dynamic_cast<Sprite<T> *>((ObjectInfos().getObjectInfo(from) -> getObject()));
    int height, width, zIndex;
    std::tie(height, width, zIndex) = sprite -> getPars();
    
    int startI, startJ;
    std::tie(startI, startJ) = sprite -> getPos();
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            spriteBitmap[startI + i][startJ + j].erase(RSprite(from, zIndex, i, j));
            ObjectId id = spriteBitmap[startI + i][startJ + j].top().objectId;
            Sprite<T> *sprite = dynamic_cast<Sprite<T> *>((ObjectInfos().getObjectInfo(id) -> getObject()));
            change[startI + i][startJ + j] = true;
            buffer[startI + i][startJ + j] = sprite -> getPixel(i, j);
            /* 务必保证有背景，优先级最低 */
            /* update(startI + i, startJ + j, sprite -> getPixel(i, j)); */
            bool needUpdate = (msg.description != "fasle");
            if (needUpdate)
            {
                update();
            }
        }
    }
}

/* singleton */
class Ncurses: public Interface<char>, virtual public DynamicRootObject
{
        Declare_Object;
        
    private:
        /* static SmartArray<char> buffer; */
        static Thread pid;
        static ObjectId sendTo;
        static bool begin;
        /* static SmartArray<std::priority_queue<ObjectId> >spriteBitmap; */
        
        void *input(void *unused);
        void update(int i, int j, char pixel);
        void update();
        
    public:
        Ncurses(SmartArray<char> b, ObjectId st);
        virtual ~Ncurses();
        void handleMessageUpdate(void *unused);
        
        void end();
};

#endif
