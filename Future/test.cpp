#include <memory>
#include <functional>
#include <thread>
#include <vector>

template <class T, class A>
class CallbackBlock
{
    public:
        typedef T RetType;
        typedef A ParaType;
        typedef std::function<RetType(ParaType)> FnType;
        
    private:
        FnType callbackFn;
        RetType retVal;
        ParaType paraVal;
        bool isValid;
        
    public:
        CallbackBlock(const FnType f, const A a);
        ~CallbackBlock();
        bool valid();
        RetType get();
};

class Future
{
    private:
        std::vector<void *> blocks;
        
    public:
        template <class T, class A>
        std::shared_ptr<CallbackBlock<T, A> >put(std::function<T(A)> f, A a);
        void begin();
        void end();
};

void Future::begin()
{
    void *block = blocks[0];
}
