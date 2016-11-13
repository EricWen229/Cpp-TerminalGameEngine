#include <cppunit/extensions/HelperMacros.h>
#include "Array.h"

class TestArray: public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(TestArray);
        CPPUNIT_TEST(testPart);
        CPPUNIT_TEST(testShare);
        CPPUNIT_TEST(testNull);
        CPPUNIT_TEST_SUITE_END();
        
    public:
        TestArray();
        ~TestArray();
        void testPart();
        void testShare();
        void testNull();
};