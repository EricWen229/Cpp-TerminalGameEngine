#include "TestArray.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestArray, "TestArray");

TestArray::TestArray() {}
TestArray::~TestArray() {}

void TestArray::testNull()
{
    SmartArray<int> sa;
    CPPUNIT_ASSERT(sa.isNull() == true);
    
    SmartArray<int> sb(sa);
    CPPUNIT_ASSERT(sb.isNull() == true);
    
    SmartArray<int> sc = sa;
    CPPUNIT_ASSERT(sc.isNull() == true);
}

void TestArray::testNoNull()
{
    SmartArray<int> sa = createArray<int>(3, 3);
    CPPUNIT_ASSERT(sa.isNull() == false);
    CPPUNIT_ASSERT(sa -> height == 3);
    CPPUNIT_ASSERT(sa -> width == 3);
    /* 简单地确认存在可赋值的内存 */
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            sa[i][j] = 0;
        }
    }
    
    SmartArray<int> sb(sa);
    CPPUNIT_ASSERT(sb -> height == 3);
    CPPUNIT_ASSERT(sb -> width == 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            CPPUNIT_ASSERT(&sb[i][j] == &sa[i][j]);
        }
    }
    
    SmartArray<int> sc = sa;
    CPPUNIT_ASSERT(sc -> height == 3);
    CPPUNIT_ASSERT(sc -> width == 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            CPPUNIT_ASSERT(&sc[i][j] == &sa[i][j]);
        }
    }
}

void TestArray::testCopy()
{
    SmartArray<int> sa;
    {
        SmartArray<int> sb = createArray<int>(3, 3);
        sa = sb;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                sb[i][j] = i + j;
            }
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            CPPUNIT_ASSERT(sa[i][j] == i + j);
        }
    }
    
    SmartArray<int> *sb = new SmartArray<int>;
    *sb = createArray<int>(3, 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            (*sb)[i][j] = i + j;
        }
    }
    SmartArray<int> sc(*sb);
    delete sb;
    for (int i = 0; i < 3; i ++)
    {
        for (int j = 0; j < 3; j++)
        {
            CPPUNIT_ASSERT(sc[i][j] == i + j);
        }
    }
}

void TestArray::testReAssign()
{
    SmartArray<int> sa;
    CPPUNIT_ASSERT(sa.isNull() == true);
    sa = createArray<int>(3, 3);
    CPPUNIT_ASSERT(sa.isNull() == false);
}

void TestArray::testCreateArrayGlobal()
{
    SmartArray<int> sInt = createArray<int>(1, 1);
    sInt[0][0] = 1;
    
    SmartArray<char> sChar = createArray<char>(1, 1);
    sChar[0][0] = ' ';
    
    class MyClass
    {};
    SmartArray<MyClass> sMyClass = createArray<MyClass>(1, 1);
    sMyClass[0][0] = MyClass();
    
    SmartArray<std::tuple<int, int, int> > sTuple =
        createArray<std::tuple<int, int, int> >(1, 1);
    sTuple[0][0] = std::tuple<int, int, int>(1, 1, 1);
    
    SmartArray<std::function<void()> > sFn = createArray<std::function<void()> >(1, 1);
    sFn[0][0] = []() {};
}

void TestArray::testCreateArrayLocal()
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
    SmartArray<int> p = createArray<int>(3, 3, arr);
    CPPUNIT_ASSERT(p[0][0] == 9);
    CPPUNIT_ASSERT(p[0][2] == 15);
    CPPUNIT_ASSERT(p[2][0] == 15);
    CPPUNIT_ASSERT(p[2][2] == 25);
    p[0][0] = 100;
    CPPUNIT_ASSERT(s[2][2] == 100);
    p[0][0] = 9;
    CPPUNIT_ASSERT(s[2][2] == 9);
    
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
    r[0][0] = 16;
    CPPUNIT_ASSERT(p[1][1] == 16);
    CPPUNIT_ASSERT(s[3][3] == 16);
    
    SmartArray<int> a = createArray<int>(1, 1, 2, 2, s);
    CPPUNIT_ASSERT(a[0][0] == 4);
    CPPUNIT_ASSERT(a[0][1] == 6);
    CPPUNIT_ASSERT(a[1][0] == 6);
    CPPUNIT_ASSERT(a[1][1] == 9);
    a[0][0] = 100;
    CPPUNIT_ASSERT(s[1][1] == 100);
    a[0][0] = 4;
    CPPUNIT_ASSERT(s[1][1] == 4);
    
    SmartArray<int> b = createArray<int>(0, 0, 1, 1, a);
    CPPUNIT_ASSERT(b[0][0] == 4);
    b[0][0] = 100;
    CPPUNIT_ASSERT(a[0][0] == 100);
    CPPUNIT_ASSERT(s[1][1] == 100);
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
