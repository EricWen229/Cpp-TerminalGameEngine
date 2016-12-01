#include "Future.h"
#include <assert.h>
#include <iostream>
#include <unistd.h>

int main()
{
    Future future;
    future.begin();
    Id id = future.putAsyncFn([](void *unused)
    {
        std::cout << "Welcome to the async world!" << std::endl;
        return nullptr;
    });
    future.putParas(id, nullptr);
    
    Id wait = future.putAsyncFn([](void *unused)
    {
        sleep(2);
        std::cout << "This is a sync function." << std::endl;
        return nullptr;
    });
    future.putParas(wait, nullptr);
    std::cout << "You can see the main thread wait for 2 seconds." << std::endl;
    future.wait(wait);
    assert(future.isReady(wait) == true);
    
    while (!future.isReady(id)) ;
    std::cout << "The async function is ready!" << std::endl;
    
    Id res = future.putAsyncFn([](void *pointer)
    {
        std::cout << "I accept parameter: ";
        std::cout << *((int *)pointer) << std::endl;
        return (void *)new int(5);
    });
    future.putParas(res, (void *)new int(2));
    future.wait(res);
    /* while (!future.isReady(res)) ; */
    std::cout << "I get the result: ";
    std::cout << *((int *)future.getResult(res)) << std::endl;
    future.end();
}
