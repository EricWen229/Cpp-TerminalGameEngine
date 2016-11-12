#include "Array.h"
#include <iostream>

int main()
{
    SmartArray<int> sa = createArray<int>(3, 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            sa[i][j] = (i + 1) * (j + 1);
        }
    }
    int *part[2] = { &sa[1][1], &sa[2][1] };
    SmartArray<int> sb = createArray<int>(2, 2, part);
    std::cout << sb[1][1] << std::endl;
}
