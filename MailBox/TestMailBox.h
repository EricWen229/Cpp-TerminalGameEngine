#include <cppunit/extensions/HelperMacros.h>
#include "MailBox.h"

int judgeHelper;

/* 下面这个对象的实现不保证在AsyncCallback下也能处理正确 */
class Test: public RootObject
{
        Declare_Class;
    public:
        Test(): RootObject() {}
        virtual ~Test()
        {
            Out_Object(Test);
        }
        void *handleMessageInterval(void *pointer)
        {
#ifdef AsyncCallback
            TopHalf(pointer, locker, msg);
            std::cout << msg.msg << std::endl;
            locker.V();
#else
            std::cout << ((Message *)pointer) -> description << std::endl;
#endif
            judgeHelper = 100;
            return null;
        }
        static void *createObject(void *)
        {
            return null;
        }
};

Implement_Class(Test)
{
    Register_Object(Test);
    Register_Fn(Test, handleMessageInterval);
}

class TestMailBox: public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(TestMailBox);
        CPPUNIT_TEST(testNormal);
        CPPUNIT_TEST(testToObjectDisappear);
        CPPUNIT_TEST(testFromObjectDisappear);
        CPPUNIT_TEST(testToFuncDisappear);
        CPPUNIT_TEST(testToFuncDisappearButReg);
        CPPUNIT_TEST_SUITE_END();
        
    public:
        TestMailBox();
        ~TestMailBox();
        
        void testNormal();
        void testToObjectDisappear();
        void testFromObjectDisappear();
        void testToFuncDisappear();
        /* 相应对象本来不存在某个处理函数 */
        /* 但是后来注册上，看是否能够正常处理 */
        void testToFuncDisappearButReg();
};
