#include "Array.h"
#include <iostream>

int main()
{
    SmartArray<int> sa = createArray<int>(3, 3);
    SmartArray<int> sb;
    std::cout << sa[0][0] << std::endl;
}
