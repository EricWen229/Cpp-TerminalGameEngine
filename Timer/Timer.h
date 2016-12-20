#ifndef Timer_H
#define Timer_H

#include "../Dynamic/ObjectDynamic.h"
#include <map>
#include <tuple>
#include <string>
#include "../Semaphore/Semaphore.h"
#include <unistd.h>

class Timer
{
    private:
        typedef std::tuple<ObjectId, const std::string> Element;
        typedef std::multimap<int, Element, std::greater<int> > Container;
        typedef typename Container::iterator Iterator;
        
        static Container container;
        static bool firstInstance;
        static Thread thread;
        
    private:
        void *loop(void *unused);
        
    public:
        void reg(ObjectId id, long int usecond, const std::string &name);
        void out(ObjectId id, const std::string &name);
        void end();
};

#endif
