#include <cppunit/extensions/HelperMacros.h>
#include "EventBuffer.h"

EventBuffer eb;

class TestEventBuffer: public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(TestEventBuffer);
        CPPUNIT_TEST(testA);
        /* CPPUNIT_TEST(testB); */
        /* CPPUNIT_TEST(testC); */
        /* CPPUNIT_TEST(testD); */
        CPPUNIT_TEST_SUITE_END();
        
    public:
        TestEventBuffer();
        ~TestEventBuffer();
        void testA();
        void testB();
        void testC();
        void testD();
};
