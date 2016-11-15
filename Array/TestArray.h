#include <cppunit/extensions/HelperMacros.h>
#include "Array.h"

class TestArray: public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(TestArray);
        CPPUNIT_TEST(testPart);
        CPPUNIT_TEST(testShare);
        CPPUNIT_TEST(testNull);
        CPPUNIT_TEST(testReassign);
        CPPUNIT_TEST(testStatic);
        CPPUNIT_TEST_SUITE_END();
        
    public:
        TestArray();
        ~TestArray();
        void testPart();
        void testShare();
        void testNull();
        /* 看一看对同一个变量重新赋值会不会导致内存泄漏 */
        void testReassign();
        void testStatic();
};
