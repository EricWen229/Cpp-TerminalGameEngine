#include <cppunit/extensions/HelperMacros.h>
#include "Array.h"

class TestArray: public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(TestArray);
        /* CPPUNIT_TEST(TestTenthFrameSpare); */
        CPPUNIT_TEST_SUITE_END();
        
    public:
        TestArray();
        ~TestArray();
};
