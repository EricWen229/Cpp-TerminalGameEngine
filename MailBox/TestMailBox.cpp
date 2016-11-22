#include "TestMailBox.h"
/* 要沉睡主线程来一定程度上达到线程同步 */
/* 但这不是百分之百的保证，不过这是最简单的方法 */
/* 为了测试单独弄个锁太麻烦了 */
#include <unistd.h>

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestMailBox, "TestMailBox");

TestMailBox::TestMailBox() {}
TestMailBox::~TestMailBox() {}

void TestMailBox::testNormal()
{
    judgeHelper = 0;
    MailBox().loop();
    Test t1, t2;
    t1.RegisterObjectInfo();
    t2.RegisterObjectInfo();
    MailBox().put(Message(t1.objectId, t2.objectId, "Interval", "I love u"));
    sleep(1);
    CPPUNIT_ASSERT(100 == judgeHelper);
    MailBox().end();
}

void TestMailBox::testToObjectDisappear()
{
    judgeHelper = 0;
    MailBox().loop();
    Test t1, t2;
    t1.RegisterObjectInfo();
    MailBox().put(Message(t1.objectId, t2.objectId, "Interval", "I love u"));
    sleep(1);
    CPPUNIT_ASSERT(0 == judgeHelper);
    MailBox().end();
}

void TestMailBox::testFromObjectDisappear()
{
    judgeHelper = 0;
    MailBox().loop();
    Test t1, t2;
    t2.RegisterObjectInfo();
    MailBox().put(Message(t1.objectId, t2.objectId, "Interval", "I love u"));
    sleep(1);
    CPPUNIT_ASSERT(100 == judgeHelper);
    MailBox().end();
}

void TestMailBox::testToFuncDisappear()
{
    judgeHelper = 0;
    MailBox().loop();
    Test t1, t2;
    t1.RegisterObjectInfo();
    t2.RegisterObjectInfo();
    t2.getObjectInfo().outDynamicFn("handleMessageInterval");
    MailBox().put(Message(t1.objectId, t2.objectId, "Interval", "I love u"));
    sleep(1);
    CPPUNIT_ASSERT(0 == judgeHelper);
    MailBox().end();
}

void TestMailBox::testToFuncDisappearButReg()
{
    judgeHelper = 0;
    MailBox().loop();
    Test t1, t2;
    t1.RegisterObjectInfo();
    t2.RegisterObjectInfo();
    t2.getObjectInfo().regDynamicFn("handleMessageIn", [&](void *p)
    {
        judgeHelper = 200;
        std::cout << ((Message *)p) -> description;
        return null;
    });
    MailBox().put(Message(t1.objectId, t2.objectId, "In", "I love u"));
    sleep(1);
    CPPUNIT_ASSERT(200 == judgeHelper);
    MailBox().end();
}
