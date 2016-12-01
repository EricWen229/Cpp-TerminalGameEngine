#include <functional>
#include <memory>
#include "../Semaphore/Semaphore.h"
#include <vector>
#include <iostream>

template <class T>
class Future;

template <class T>
class PromisePointer;

template <class T>
class Promise
{
    private:
        static int referenceCount;
        std::function<T()> fn;
        bool isValid;
        T value;
        
        template <class S>
        friend class Future;
        
        template <class S>
        friend class PromisePointer;
        
    public:
        Promise(std::function<T()> f);
        bool valid();
        T get();
};

template <class T>
int Promise<T>::referenceCount = 0;

template <class T>
class PromisePointer
{
    private:
        Promise<T> *pointer;
        
    public:
        PromisePointer();
        PromisePointer(Promise<T> *p);
        PromisePointer(const PromisePointer &p);
        PromisePointer &operator=(const PromisePointer &p);
        ~PromisePointer();
        
        Promise<T> *operator->();
        bool isNull() const;
};

template <class T>
PromisePointer<T>::PromisePointer(): pointer(nullptr) {}

template <class T>
PromisePointer<T>::PromisePointer(Promise<T> *p): pointer(p) {}

template <class T>
PromisePointer<T>::PromisePointer(const PromisePointer &p): pointer(p.pointer)
{
    if (!isNull())
    {
        pointer -> referenceCount++;
    }
}

template <class T>
PromisePointer<T> &PromisePointer<T>::operator=(const PromisePointer &p)
{
    if (&p == this)
    {
        return *this;
    }
    if (!isNull())
    {
        pointer -> referenceCount--;
        if (pointer -> referenceCount == 0)
        {
            delete pointer;
        }
    }
    if (!p.isNull())
    {
        p.pointer -> referenceCount++;
    }
    pointer = p.pointer;
}

template <class T>
PromisePointer<T>::~PromisePointer()
{
    if (!isNull())
    {
        pointer -> referenceCount--;
        if (pointer -> referenceCount == 0)
        {
            delete pointer;
        }
    }
}

template <class T>
Promise<T> *PromisePointer<T>::operator->()
{
    return pointer;
}

template <class T>
bool PromisePointer<T>::isNull() const
{
    return pointer == nullptr;
}

template <class T>
Promise<T>::Promise(std::function<T()> f): fn(f) {}

template <class T>
bool Promise<T>::valid()
{
    return isValid;
}

template <class T>
T Promise<T>::get()
{
    return value;
}

template <class T>
class Future
{
    private:
        bool exit;
        Semaphore s;
        std::thread thread;
        std::vector<PromisePointer<T> > promises;
        
    public:
        Future();
        ~Future();
        PromisePointer<T> put(std::function<T()> fn);
};

template <class T>
PromisePointer<T> Future<T>::put(std::function<T()> fn)
{
    PromisePointer<T> p = PromisePointer<T>(new Promise<T>(fn));
    promises.push_back(p);
    s.V();
    return p;
}

template <class T>
Future<T>::Future(): exit(false)
{
    std::function<void()> loop =
        [&]()
    {
        while (!exit)
        {
            s.P();
            PromisePointer<T> promise = promises.front();
            promise -> value = promise -> fn();
            promise -> isValid = true;
            promises.erase(promises.begin());
        }
    };
    thread = std::thread(loop);
}

template <class T>
Future<T>::~Future()
{
    exit = true;
    thread.detach();
}

int main()
{
    Future<int> future;
    auto p = future.put([]()
    {
        return 1;
    });
    std::cout << "Hello" << std::endl;
    while (!p -> valid()) ;
    std::cout << p -> get() << std::endl;
}
