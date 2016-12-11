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
        SmartArray<pQueue<RSprite> > bitmap;
        virtual void update(int i, int j, T pixel) = 0;
        
    public:
        Interface(int height, int width);
        virtual ~Interface();
        
        virtual void handleMessageUpdate(void *p) = 0;
        void handleMessageSpriteApp(void *p);
        void handleMessageSpriteDis(void *p);
};

template <class T>
Interface<T>::Interface(int height, int width)
{
    bitmap = createArray<pQueue<RSprite> >(height, width);
}

template <class T>
Interface<T>::~Interface() {}

template <class T>
void Interface<T>::handleMessageSpriteApp(void *p)
{
    Message msg = *((Message *)p);
    ObjectId from = msg.from;
    Sprite<T> *sprite = (Sprite<T> *)(ObjectInfos().getObjectInfo(from) -> getObject());
    int height, width, zIndex;
    std::tie(height, width, zIndex) = sprite -> getPars();
    
    const std::string &des = msg.description;
    std::string::size_type split = des.find(' ');
    int startI = std::stoi(des.substr(0, split));
    int startJ = std::stoi(des.substr(split + 1));
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            bitmap[startI + i][startJ + j].push(RSprite(from, zIndex));
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (bitmap[startI + i][startJ + j].top().objectId == from)
            {
                update(startI + i, startJ + j, sprite -> getPixel(i, j));
            }
        }
    }
}

template <class T>
void Interface<T>::handleMessageSpriteDis(void *p)
{
    Message msg = *((Message *)p);
    ObjectId from = msg.from;
    Sprite<T> *sprite = (Sprite<T> *)(ObjectInfos().getObjectInfo(from) -> getObject());
    int height, width, zIndex;
    std::tie(height, width, zIndex) = sprite -> getPars();
    
    const std::string &des = msg.description;
    std::string::size_type split = des.find(' ');
    int startI = std::stoi(des.substr(0, split));
    int startJ = std::stoi(des.substr(split + 1));
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            bitmap[startI + i][startJ + j].erase(RSprite(from, zIndex));
            ObjectId id = bitmap[startI + i][startJ + j].top();
            Sprite<T> *sprite = (Sprite<T> *)(ObjectInfos().getObjectInfo(id) -> getObject());
            /* 务必保证有背景，优先级最低 */
            update(startI + i, startJ + j, sprite -> getPixel(i, j));
        }
    }
}

/* singleton */
class Ncurses: public Interface<char>, virtual public DynamicRootObject
{
        Declare_Object;
        
    private:
        static SmartArray<char> buffer;
        static Thread pid;
        static ObjectId sendTo;
        static bool begin;
        static SmartArray<std::priority_queue<ObjectId> >bitmap;
        
        void *input(void *unused);
        void update(int i, int j, char pixel);
        
    public:
        Ncurses(SmartArray<char> b, ObjectId st);
        virtual ~Ncurses();
        void handleMessageUpdate(void *unused);
        
        void end();
};

#endif
