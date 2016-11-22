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
    Thread p[] =
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
    Thread p[] =
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
    Thread p[] =
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
    Thread p[] =
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

void TestEventBuffer::testE()
{
    Thread p[] =
    {
        createPthread(put),
        createPthread(get),
        createPthread(put),
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

void TestEventBuffer::testF()
{
    Thread p[] =
    {
        createPthread(put),
        createPthread(get),
        createPthread(get),
        createPthread(put),
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

void TestEventBuffer::testG()
{
    Thread p[] =
    {
        createPthread(put),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(put),
        createPthread(get),
        createPthread(get),
        createPthread(get)
    };
    
    for (int i = 0; i < 8; i++)
    {
        waitPthread(p[i]);
    }
}

void TestEventBuffer::testH()
{
    Thread p[] =
    {
        createPthread(put),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(put),
        createPthread(get),
        createPthread(get)
    };
    
    for (int i = 0; i < 8; i++)
    {
        waitPthread(p[i]);
    }
}

void TestEventBuffer::testI()
{
    Thread p[] =
    {
        createPthread(put),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(put),
        createPthread(get)
    };
    
    for (int i = 0; i < 8; i++)
    {
        waitPthread(p[i]);
    }
}

void TestEventBuffer::testJ()
{
    Thread p[] =
    {
        createPthread(put),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(put)
    };
    
    for (int i = 0; i < 8; i++)
    {
        waitPthread(p[i]);
    }
}

void TestEventBuffer::testK()
{
    Thread p[] =
    {
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(get),
        createPthread(put),
        createPthread(put)
    };
    
    for (int i = 0; i < 8; i++)
    {
        waitPthread(p[i]);
    }
}
