#ifndef Queue_H
#define Queue_H

#include <set>
#include <list>
#include <iostream>
#include "../Dynamic/ObjectDynamic.h"
#include "../DiagHelper.h"

template <class T>
class pQueue
{
    private:
        std::multiset<T, std::greater<T> > container;
        
    public:
        bool empty();
        const T &top();
        void pop();
        void push(const T &value);
        void erase(const T &value);
        bool exist(const T &value);
};

class PQueue
{
    private:
        std::list<ObjectId> container;
        
    public:
        bool empty() const;
        const ObjectId top() const;
        void pop();
        void push(const ObjectId id);
        void erase(const ObjectId id);
        bool exist(const ObjectId id) const;
};

template <class T>
bool pQueue<T>::empty()
{
    return container.empty();
}

template <class T>
const T &pQueue<T>::top()
{
    Assert(empty() == false);
    return *(container.begin());
}

template <class T>
void pQueue<T>::pop()
{
    Assert(empty() == false);
    container.erase(container.begin());
}

template <class T>
void pQueue<T>::push(const T &value)
{
    ExtraRun
    (
        typename std::set<T>::const_iterator it = container.find(value);
        Assert(it == container.end());
    );
    container.insert(value);
}

template <class T>
void pQueue<T>::erase(const T &value)
{
    typename std::set<T>::const_iterator it = container.find(value);
    if (it != container.end())
    {
        container.erase(it);
    }
}

template <class T>
bool pQueue<T>::exist(const T &value)
{
    return false;
}

#endif
