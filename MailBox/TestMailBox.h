#include <cppunit/extensions/HelperMacros.h>
#include "MailBox.h"


class TestMailBox: public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(TestMailBox);
        /* CPPUNIT_TEST(testK); */
        CPPUNIT_TEST_SUITE_END();
        
    public:
        TestMailBox();
        ~TestMailBox();
};
