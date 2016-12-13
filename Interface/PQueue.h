#ifndef Queue_H
#define Queue_H

#include <set>
#include <iostream>
#include "../DiagHelper.h"

template <class T>
class pQueue
{
    private:
        std::set<T, std::greater<T> > container;
        
    public:
        bool empty();
        const T &top();
        void pop();
        void push(const T &value);
        void erase(const T &value);
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
    /* ExtraRun */
    /* ( */
    /*     typename std::set<T>::const_iterator it = container.find(value); */
    /*     Assert(it == container.end()); */
    /* ); */
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

#endif
