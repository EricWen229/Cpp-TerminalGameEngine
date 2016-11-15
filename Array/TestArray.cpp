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
    
    int **arr = new int *[3];
    arr[0] = &s[2][2];
    arr[1] = &s[3][2];
    arr[2] = &s[4][2];
    /* { */
    /*     &s[2][2], */
    /*     &s[3][2], */
    /*     &s[4][2] */
    /* }; */
    SmartArray<int> p = createArray<int>(3, 3, arr);
    CPPUNIT_ASSERT(p[0][0] == 9);
    CPPUNIT_ASSERT(p[0][2] == 15);
    CPPUNIT_ASSERT(p[2][0] == 15);
    CPPUNIT_ASSERT(p[2][2] == 25);
    
    p[0][0] = 100;
    CPPUNIT_ASSERT(s[2][2] == 100);
    
    int **brr = new int *[2];
    brr[0] = &p[1][1];
    brr[1] = &p[2][1];
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

void TestArray::testReassign()
{
    SmartArray<int> sa;
    sa = createArray<int>(3, 3);
    sa = createArray<int>(4, 4);
}

void TestArray::testStatic()
{
    static SmartArray<int> sa;
    sa = createArray<int>(3, 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            sa[i][j] = (i + 1) * (j + 1);
        }
    }
}
