#include "Random.h"
#include <iostream>

int main()
{
    Random r(2, 6);
    std::cout << r.get() << std::endl;
    std::cout << r.get() << std::endl;
    std::cout << r.get() << std::endl;
    std::cout << r.get() << std::endl;
    std::cout << r.get() << std::endl;
    std::cout << r.get() << std::endl;
}
