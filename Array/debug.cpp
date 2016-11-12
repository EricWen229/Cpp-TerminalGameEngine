#include "Array.h"
#include <assert.h>

#define ShowProblem

#ifdef ShowProblem
    #include <iostream>
    #define CPPUNIT_ASSERT(x) (std::cout << (x) << std::endl)
#else
    #define CPPUNIT_ASSERT assert
#endif

void testPart()
{
    SmartArray<int> s = createArray<int>(5, 5);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            s[i][j] = (i + 1) * (j + 1);
        }
    }
    
    int *arr[3] =
    {
        &s[2][2],
        &s[3][2],
        &s[4][2]
    };
    SmartArray<int> p = createArray<int>(3, 3, arr);
    CPPUNIT_ASSERT(p[0][0] == 9);
    CPPUNIT_ASSERT(p[0][2] == 15);
    CPPUNIT_ASSERT(p[2][0] == 15);
    CPPUNIT_ASSERT(p[2][2] == 25);
    
    p[0][0] = 100;
    CPPUNIT_ASSERT(s[2][2] == 100);
    
    int *brr[2] =
    {
        &p[1][1],
        &p[2][1]
    };
    SmartArray<int> r = createArray<int>(2, 2, brr);
    CPPUNIT_ASSERT(r[0][0] == 16);
    CPPUNIT_ASSERT(r[0][1] == 20);
    CPPUNIT_ASSERT(r[1][0] == 20);
    CPPUNIT_ASSERT(r[1][1] == 25);
    
    r[0][0] = 200;
    CPPUNIT_ASSERT(p[1][1] == 200);
    CPPUNIT_ASSERT(s[3][3] == 200);
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            s[i][j] = (i + 1) * (j + 1);
        }
    }
    SmartArray<int> q = createArray<int>(1, 1, 2, 2, p);
    CPPUNIT_ASSERT(q[0][0] == 16);
    CPPUNIT_ASSERT(q[0][1] == 20);
    CPPUNIT_ASSERT(q[1][0] == 20);
    CPPUNIT_ASSERT(q[1][1] == 25);
    q[1][1] = 200;
    CPPUNIT_ASSERT(p[2][2] == 200);
    CPPUNIT_ASSERT(s[4][4] == 200);
}

void testSimple()
{
    SmartArray<int> p = createArray<int>(2, 2);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            p[i][j] = (i + 1) * (j + 1);
        }
    }
    SmartArray<int> q = createArray<int>(1, 1, 1, 1, p);
    CPPUNIT_ASSERT(q[0][0] == 4);
}

void testTwo()
{
    SmartArray<int> p = createArray<int>(10, 10);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            p[i][j] = (i + 1) * (j + 1);
        }
    }
    SmartArray<int> q = createArray<int>(1, 1, 5, 5, p);
    CPPUNIT_ASSERT(q[0][0] == 4);
}

int main()
{
    testSimple();
    testTwo();
    /* testPart(); */
}
