#include <functional>
#include <memory>
#include "../Semaphore/Semaphore.h"
#include <vector>
#include <iostream>

template <class T>
class Future;

template <class T>
class Promise
{
    private:
        std::function<T()> fn;
        bool isValid;
        T value;
        
        template <class S>
        friend class Future;
        
    public:
        Promise(std::function<T()> f);
        bool valid();
        T get();
};

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
        Semaphore s;
        std::vector<std::shared_ptr<Promise<T> > > promises;
        
    public:
        Future();
        std::shared_ptr<Promise<T> > put(std::function<T()> fn);
};

template <class T>
std::shared_ptr<Promise<T> > Future<T>::put(std::function<T()> fn)
{
    Promise<T> *p = new Promise<T>(fn);
    promises.push_back(std::shared_ptr<Promise <T> >(p));
    s.V();
    return std::shared_ptr<Promise<T> >(p);
}

template <class T>
Future<T>::Future()
{
    std::function<void()> loop =
        [&]()
    {
        s.P();
        std::shared_ptr<Promise<T> > promise = promises.front();
        promise -> value = promise -> fn();
        promises.erase(promises.begin());
    };
    std::thread t(loop);
}

int main()
{
    Future<int> future;
    auto p = future.put([]()
    {
        return 1;
    });
    while (!p -> valid()) ;
    std::cout << p -> get() << std::endl;
}
