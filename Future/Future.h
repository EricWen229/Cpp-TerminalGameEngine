#ifndef Future_H
#define Future_H

#include "../Semaphore/Semaphore.h"
#include <map>
#include <set>
#include <functional>
#include <tuple>
#include <assert.h>

#define RegisterType1(Type1) \
    typedef Type1 ParaType1
#define RegisterType2(Type1, Type2) \
    typedef Type1 ParaType1 \
    typedef Type2 ParaType2

#define TranParas1(value1) \
    (void*)&value1

typedef unsigned int Id;

class getId
{
    private:
        static Id id;
        
    public:
        Id operator()();
};

class Future
{
    private:
        typedef std::function<void *(void *)> AsyncFnType;
        typedef bool HasProvideParas;
        typedef bool HasProvideResult;
        typedef void *ParasType;
        typedef void *ResultType;
        typedef std::tuple
        <AsyncFnType, ParasType, ResultType,
        HasProvideParas, HasProvideResult>
        EleType;
        typedef std::map<Id, EleType> ContainerType;
        
    private:
        ContainerType container;
        std::set<Id> active;
        Semaphore mutex;
        Semaphore fnResourse;
        Thread thread;
        bool isExit;
        
    public:
        Future();
        void begin();
        void end();
        
    public:
        Id putAsyncFn(AsyncFnType);
        bool putParas(Id id, ParasType paras);
        bool isReady(Id id);
        void wait(Id id);
        ResultType getResult(Id id);
};

#endif
