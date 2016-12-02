#include "TestSemaphore.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestSemaphore, "TestSemaphore");

TestSemaphore::TestSemaphore() {}
TestSemaphore::~TestSemaphore() {}

void TestSemaphore::testSPositive()
{
    Semaphore s;
    CPPUNIT_ASSERT(s.get() == 0);
    for (int i = 0; i < 1000; i++)
    {
        s.V();
        CPPUNIT_ASSERT(s.get() == i + 1);
    }
}

void TestSemaphore::testSNegative()
{
    Semaphore s;
    CPPUNIT_ASSERT(s.get() == 0);
    std::thread threads[20];
    for (int i = 0; i < 20; i++)
    {
        threads[i] = std::thread([&]()
        {
            s.P();
        });
        CPPUNIT_ASSERT(s.get() == -1 * (i + 1));
    }
    for (int i = 0; i < 20; i++)
    {
        s.V();
    }
    for (int i = 0; i < 20; i++)
    {
        threads[i].join();
    }
}

void TestSemaphore::testWakeUp()
{
    std::atomic_int count(0);
    Semaphore s;
    CPPUNIT_ASSERT(s.get() == 0);
    std::thread threads[20];
    for (int i = 0; i < 20; i++)
    {
        threads[i] = std::thread([=, &count, &s]()
        {
            s.P();
            count += i;
        });
        CPPUNIT_ASSERT(s.get() == -1 * (i + 1));
    }
    for (int i = 0; i < 20; i++)
    {
        s.V();
    }
    for (int i = 0; i < 20; i++)
    {
        threads[i].join();
    }
    CPPUNIT_ASSERT(count == std::atomic_int((0 + 19) * 20 / 2));
}
