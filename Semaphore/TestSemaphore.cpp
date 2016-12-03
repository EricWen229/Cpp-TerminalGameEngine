#include "TestSemaphore.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestSemaphore, "TestSemaphore");

TestSemaphore::TestSemaphore() {}
TestSemaphore::~TestSemaphore() {}

void TestSemaphore::testSPositive()
{
    Semaphore s;
    CPPUNIT_ASSERT(s.get() == 0);
    for (int i = 0; i < 100; i++)
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
    }
    sleep(1);
    CPPUNIT_ASSERT(s.get() == -20);
    for (int i = 0; i < 20; i++)
    {
        s.V();
    }
    for (int i = 0; i < 20; i++)
    {
        threads[i].join();
    }
    CPPUNIT_ASSERT(s.get() == 0);
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

void TestSemaphore::testDeadlock()
{
    Semaphore mutex(1);
    Semaphore s(1);
    
    std::function<void()> fn = [&]()
    {
        mutex.P();
        usleep(2);
        s.P();
        usleep(2);
        s.V();
        mutex.V();
    };
    
    std::thread threads[20];
    for (int i = 0; i < 20; i++)
    {
        threads[i] = std::thread(fn);
    }
    for (int i = 0; i < 20; i++)
    {
        threads[i].join();
    }
}

void TestSemaphore::testProducerConsumer()
{
    Semaphore mutex(1);
    Semaphore s;
    std::function<void()> producerA = [&]()
    {
        mutex.P();
        usleep(1);
        s.V();
        mutex.V();
    };
    std::function<void()> producerB = [&]()
    {
        mutex.P();
        usleep(3);
        s.V();
        mutex.V();
    };
    std::function<void()> consumer = [&]()
    {
        usleep(1);
        s.P();
        mutex.P();
        usleep(2);
        mutex.V();
    };
    std::thread threads[20];
    
    for (int i = 0; i < 10; i++)
    {
        threads[i] = std::thread(producerA);
    }
    for (int i = 0; i < 10; i++)
    {
        threads[i + 10] = std::thread(consumer);
    }
    for (int i = 0; i < 20; i++)
    {
        threads[i].join();
    }
    
    for (int i = 0; i < 10; i++)
    {
        threads[i] = std::thread(consumer);
    }
    for (int i = 0; i < 10; i++)
    {
        threads[i + 10] = std::thread(producerB);
    }
    for (int i = 0; i < 20; i++)
    {
        threads[i].join();
    }
}

void TestSemaphore::testNoCopy()
{
    Semaphore s;
    /* Semaphore x = s; */
    /* Semaphore y(s); */
}
