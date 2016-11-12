#include "TestArray.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestArray, "TestArray");

TestArray::TestArray() {}
TestArray::~TestArray() {}

void TestArray::testPart()
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
    CPPUNIT_ASSERT(p[2][2] == 25);
    
    p[0][0] = 100;
    CPPUNIT_ASSERT(s[2][2] == 100);
    
    SmartArray<int> q = createArray<int>(1, 1, 2, 2, p);
    CPPUNIT_ASSERT(q[1][1] == 25);
    q[1][1] = 200;
    /* CPPUNIT_ASSERT(p[2][2] == 200); */
    /* CPPUNIT_ASSERT(s[4][4] == 200); */
}

void TestArray::testShare()
{
    SmartArray<int> sa = createArray<int>(4, 4);
    SmartArray<int> sb = sa;
    sb[3][3] = 100;
    CPPUNIT_ASSERT(sa[3][3] == 100);
}

void TestArray::testNull()
{
    SmartArray<int> sa;
    CPPUNIT_ASSERT(sa.isNull() == true);
}
