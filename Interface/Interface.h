#ifndef Interface_H
#define Interface_H

#include "../Array/Array.h"
#include "../Dynamic/ObjectDynamic.h"
#include "../MailBox/MailBox.h"
#include "Sprite.h"
#include "PQueue.h"
#include <functional>
#include <ncurses.h>

/* class Sprite; */

template <class T>
class Interface
{
    private:
        SmartArray<pQueue<ObjectId> > bitmap;
        virtual void update(int i, int j, T pixel) = 0;
        
    public:
        Interface(int height, int width)
        {
            bitmap = createArray<pQueue<ObjectId> >(height, width);
        }
        virtual ~Interface() {}
        
        void handleMessageSpriteApp(void *p)
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
                    update(startI + i, startJ + j, sprite -> getPixel(i, j));
                }
            }
        }
        void handleMessageSpriteDis(void *p)
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
                    update(startI + i, startJ + j, sprite -> getPixel(i, j));
                }
            }
        }
};

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
        virtual void handleMessageUpdate(void *unused);
        /* Dis means diappear */
        virtual void handleMessageSpriteDis(void *unused);
        /* App means appear */
        virtual void handleMessageSpriteApp(void *unused);
        
    public:
        Ncurses(SmartArray<char> b, ObjectId st);
        virtual ~Ncurses();
        
        void end();
};

#endif
