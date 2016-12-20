#ifndef Timer_H
#define Timer_H

#include "../Dynamic/ObjectDynamic.h"
#include <map>
#include <tuple>

class Timer
{
    private:
        static int count;
        static bool isExit;
        
        typedef std::tuple<ObjectId, std::string, void *> Element;
        typedef std::multimap<int, Element> Container;
        static Container container;
        
    private:
        void *loopHelper(void *unused);
        
    public:
        void reg
        (ObjectId id,
         std::string funcName,
         void *paras, int fre);
        void out
        (
            ObjectId id,
            std::string funcName
        );
        void loop();
        void end();
};

#endif
