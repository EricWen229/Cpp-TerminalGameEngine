#include "TestEventBuffer.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestEventBuffer, "TestEventBuffer");

TestEventBuffer::TestEventBuffer() {}
TestEventBuffer::~TestEventBuffer() {}

extern EventBuffer eb;

void *get(void *unused)
{
    Event e = eb.get();
    std::cout << e << std::endl;
    return null;
}

void *put(void *unused)
{
    /* sleep(1); */
    eb.put(Up);
    /* sleep(2); */
    eb.put(Right);
    eb.put(Left);
    return null;
}

void TestEventBuffer::testA()
{
    pthread_t p[] =
    {
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(put)
    };
    
    for (int i = 0; i < 4; i++)
    {
        waitPthread(p[i]);
    }
}

void TestEventBuffer::testB()
{
    pthread_t p[] =
    {
        createPthread(get),
        createPthread(get),
        createPthread(put),
        createPthread(get)
    };
    
    for (int i = 0; i < 4; i++)
    {
        waitPthread(p[i]);
    }
}

void TestEventBuffer::testC()
{
    pthread_t p[] =
    {
        createPthread(put),
        createPthread(get),
        createPthread(get),
        createPthread(get)
    };
    
    for (int i = 0; i < 4; i++)
    {
        waitPthread(p[i]);
    }
}

void TestEventBuffer::testD()
{
    pthread_t p[] =
    {
        createPthread(put),
        createPthread(put),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(get)
    };
    
    for (int i = 0; i < 8; i++)
    {
        waitPthread(p[i]);
    }
}
