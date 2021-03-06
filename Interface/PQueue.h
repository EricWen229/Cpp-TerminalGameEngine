#ifndef Queue_H
#define Queue_H

#include <set>
#include <iostream>
#include "../DiagHelper.h"

template <class T>
class pQueue
{
    private:
        std::multiset<T, std::greater<T> > container;
        
    public:
        bool empty() const;
        const T &top() const;
        void pop();
        void push(const T &value);
        void erase(const T &value);
        bool exist(const T &value) const;
        
        typedef typename std::multiset<T, std::greater<T> >::iterator Iterator;
        Iterator begin();
        Iterator end();
};

template <class T>
bool pQueue<T>::empty() const
{
    return container.empty();
}

template <class T>
const T &pQueue<T>::top() const
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
    Assert(it != container.end());
    container.erase(it);
}

template <class T>
bool pQueue<T>::exist(const T &value) const
{
    typename std::set<T>::const_iterator it = container.find(value);
    return it != container.end();
}

template <class T>
typename pQueue<T>::Iterator pQueue<T>::begin()
{
    return container.begin();
}

template <class T>
typename pQueue<T>::Iterator pQueue<T>::end()
{
    return container.end();
}

#endif
