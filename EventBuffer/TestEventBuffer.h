#include <cppunit/extensions/HelperMacros.h>
#include "EventBuffer.h"

EventBuffer eb;

class TestEventBuffer: public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(TestEventBuffer);
        /* 非常无奈，需要大量的测试来提高对正确性的自信 */
        CPPUNIT_TEST(testA);
        CPPUNIT_TEST(testB);
        CPPUNIT_TEST(testC);
        CPPUNIT_TEST(testD);
        CPPUNIT_TEST(testE);
        CPPUNIT_TEST(testF);
        CPPUNIT_TEST(testG);
        CPPUNIT_TEST(testH);
        CPPUNIT_TEST(testI);
        CPPUNIT_TEST(testJ);
        CPPUNIT_TEST(testK);
        CPPUNIT_TEST_SUITE_END();
        
    public:
        TestEventBuffer();
        ~TestEventBuffer();
        void testA();
        void testB();
        void testC();
        void testD();
        void testE();
        void testF();
        void testG();
        void testH();
        void testI();
        void testJ();
        void testK();
};
