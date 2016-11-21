#include <cppunit/extensions/HelperMacros.h>
#include "Dynamic.h"
#include "Example.h"

class GrandSon: public Son
{
        Declare_Class;
    public:
        GrandSon(): objectId(GetObjectId()()) {}
        static void *createObject(void *)
        {
            return new GrandSon;
        }
        void *sayHi(void *p)
        {
            return null;
        }
};

Implement_Class(GrandSon)
{
    Register_Object(GrandSon);
    Register_Fn(GrandSon, sayHi);
}

class TestDynamic: public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(TestDynamic);
        CPPUNIT_TEST(testGetName_S);
        CPPUNIT_TEST(testGetContructor_S);
        CPPUNIT_TEST(testRegClass);
        CPPUNIT_TEST(testOutClass);
        CPPUNIT_TEST(testRegDynamicFn);
        CPPUNIT_TEST(testOutDynamicFn);
        CPPUNIT_TEST(testGetObjectId);
        CPPUNIT_TEST(testGetDynamicFnByIdAndStr);
        CPPUNIT_TEST_SUITE_END();
        
    public:
        TestDynamic();
        ~TestDynamic();
        
        void testGetName_S();
        void testGetContructor_S();
        void testRegClass();
        void testOutClass();
        /* have been tested in other test functions */
        /* void testGetClassInfo(); */
        void testRegDynamicFn();
        void testOutDynamicFn();
        /* have been tested in other test functions */
        /* void testGetDynamicFn(); */
        void testGetObjectId();
        void testGetDynamicFnByIdAndStr();
};
