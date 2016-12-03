/* 1.类信息的注册、注销、查询 */
/* 2.对象信息的注册（由构造函数完成）、注销、查询 */
/* 3.类信息、对象信息的查询是否具有多态性 */
/* 4.直接构造的对象能否通过查询得到函数 */
/* 5.通过查询构造的对象能否通过查询得到函数 */
/* 6.能否对某对象动态添加删除成员函数 */
/* 7.dynamic_cast能否成功 */
/* 8.验证对于模板类是否具有多态性 */

/* 1.testClassInfo */
/* 2.testObjectInfo */
/* 3.testSearchPoly */
/* 4.testGetDirectObjectFn */
/* 5.testGetSearchObjectFn */
/* 6.testDynamicFn */
/* 7.testDynamicCast */

#include <cppunit/extensions/HelperMacros.h>
#include "Dynamic.h"

class Base: virtual public DynamicRootObject
{
        Declare_Class;
        Declare_Object;
    public:
        Base() {}
        virtual ~Base() {}
        static Base *createObject(void *unused)
        {
            return new Base;
        }
        void *get(void *unused)
        {
            return (void *)1;
        }
};

Implement_Class(Base);

Implement_Object(Base)
{
    Register_Object(Base);
    Register_Fn(Base, get);
}

class Derived: public Base
{
        Declare_Class;
        Declare_Object;
    public:
        Derived() {}
        virtual ~Derived() {}
        static Derived *createObject(void *unused);
        void *get(void *unused)
        {
            return (void *)2;
        }
};

Implement_Class(Derived);

Implement_Object(Derived)
{
    Register_Object(Derived);
    Register_Fn(Derived, get);
}

class TestDynamic: public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(TestDynamic);
        CPPUNIT_TEST(testClassInfo);
        CPPUNIT_TEST(testObjectInfo);
        CPPUNIT_TEST(testSearchPoly);
        CPPUNIT_TEST(testGetDirectObjectFn);
        CPPUNIT_TEST(testGetSearchObjectFn);
        CPPUNIT_TEST(testDynamicFn);
        CPPUNIT_TEST(testDynamicCast);
        CPPUNIT_TEST_SUITE_END();
        
    public:
        TestDynamic();
        ~TestDynamic();
        
        void testClassInfo();
        void testObjectInfo();
        void testSearchPoly();
        void testGetDirectObjectFn();
        void testGetSearchObjectFn();
        void testDynamicFn();
        void testDynamicCast();
};
