#include "Future.h"
#include <iostream>

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
    while (!future.isReady(id)) ;
    std::cout << "The async function is ready!" << std::endl;
    future.end();
}
