#include <cppunit/extensions/HelperMacros.h>
#include "EventBuffer.h"

class TestEventBuffer: public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(TestEventBuffer);
        /* CPPUNIT_TEST(testNull); */
        CPPUNIT_TEST_SUITE_END();
        
    public:
        TestEventBuffer();
        ~TestEventBuffer();
};
