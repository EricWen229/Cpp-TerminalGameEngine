#include "TestDynamic.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestDynamic, "TestDynamic");

TestDynamic::TestDynamic() {}
TestDynamic::~TestDynamic() {}

void TestDynamic::testGetName_S()
{
    Father::RegisterClassInfo();
    Son::RegisterClassInfo();
    GrandSon::RegisterClassInfo();
    
    Father *f =
        (Father *)ClassInfos().getClassInfo("Father")
        -> getConstructor()(null, 0);
    Father *s =
        (Father *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null, 0);
    Father *g =
        (Father *)ClassInfos().getClassInfo("GrandSon")
        -> getConstructor()(null, 0);
        
    CPPUNIT_ASSERT(f -> getClassInfo().getName() == "Father");
    CPPUNIT_ASSERT(s -> getClassInfo().getName() == "Son");
    CPPUNIT_ASSERT(g -> getClassInfo().getName() == "GrandSon");
    
    delete f;
    delete s;
    delete g;
}

void TestDynamic::testGetContructor_S()
{
    Father::RegisterClassInfo();
    Son::RegisterClassInfo();
    GrandSon::RegisterClassInfo();
    
    Father *f =
        (Father *)ClassInfos().getClassInfo("Father")
        -> getConstructor()(null, 0);
    Father *s =
        (Father *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null, 0);
    Father *g =
        (Father *)ClassInfos().getClassInfo("GrandSon")
        -> getConstructor()(null, 0);
        
    CPPUNIT_ASSERT
    (f -> getClassInfo().getConstructor()
     == (ClassInfo::ConFn)Father::createObject);
    CPPUNIT_ASSERT
    (s -> getClassInfo().getConstructor()
     == (ClassInfo::ConFn)Son::createObject);
    CPPUNIT_ASSERT
    (g -> getClassInfo().getConstructor()
     == (ClassInfo::ConFn)GrandSon::createObject);
     
    Father *ff = (Father *)f -> getClassInfo().getConstructor()(null, 0);
    Father *ss = (Father *)s -> getClassInfo().getConstructor()(null, 0);
    Father *gg = (Father *)g -> getClassInfo().getConstructor()(null, 0);
    
    CPPUNIT_ASSERT(ff -> getClassInfo().getName() == "Father");
    CPPUNIT_ASSERT(ss -> getClassInfo().getName() == "Son");
    CPPUNIT_ASSERT(gg -> getClassInfo().getName() == "GrandSon");
    
    delete f;
    delete s;
    delete g;
    
    delete ff;
    delete ss;
    delete gg;
}

void TestDynamic::testRegClass()
{
    ClassInfos().outClass("Father");
    CPPUNIT_ASSERT(ClassInfos().getClassInfo("Father") == null);
    Father::RegisterClassInfo();
    CPPUNIT_ASSERT(ClassInfos().getClassInfo("Father") != null);
}

void TestDynamic::testOutClass()
{
    Father::RegisterClassInfo();
    ClassInfos().outClass("Father");
    CPPUNIT_ASSERT(ClassInfos().getClassInfo("Father") == null);
}

void TestDynamic::testRegDynamicFn()
{
    Father::RegisterClassInfo();
    Son::RegisterClassInfo();
    GrandSon::RegisterClassInfo();
    
    Father *f =
        (Father *)ClassInfos().getClassInfo("Father")
        -> getConstructor()(null, 0);
    Father *s =
        (Father *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null, 0);
    Father *g =
        (Father *)ClassInfos().getClassInfo("GrandSon")
        -> getConstructor()(null, 0);
        
    f -> RegisterObjectInfo();
    g -> RegisterObjectInfo();
    s -> RegisterObjectInfo();
    
    CPPUNIT_ASSERT(f -> getObjectInfo().getDynamicFn("sayHello") != null);
    CPPUNIT_ASSERT(s -> getObjectInfo().getDynamicFn("sayHello") != null);
    CPPUNIT_ASSERT(g -> getObjectInfo().getDynamicFn("sayHi") != null);
    
    int arr[] = { 1 };
    f -> getObjectInfo().getDynamicFn("sayHello")((void *)arr, 1);
    s -> getObjectInfo().getDynamicFn("sayHello")((void *)arr, 1);
    g -> getObjectInfo().getDynamicFn("sayHi")((void *)arr, 1);
    
    g -> getObjectInfo().regDynamicFn
    ("Test", [](void *, int)->void * {return null;});
    g -> getObjectInfo().getDynamicFn("Test")(null, 0);
    
    delete f;
    delete s;
    delete g;
}

void TestDynamic::testOutDynamicFn()
{
    Father::RegisterClassInfo();
    Son::RegisterClassInfo();
    GrandSon::RegisterClassInfo();
    
    Father *f =
        (Father *)ClassInfos().getClassInfo("Father")
        -> getConstructor()(null, 0);
    Father *s =
        (Father *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null, 0);
    Father *g =
        (Father *)ClassInfos().getClassInfo("GrandSon")
        -> getConstructor()(null, 0);
        
    f -> RegisterObjectInfo();
    g -> RegisterObjectInfo();
    s -> RegisterObjectInfo();
    
    f -> getObjectInfo().outDynamicFn("sayHello");
    f -> getObjectInfo().outDynamicFn("sayHi");
    g -> getObjectInfo().outDynamicFn("sayHello");
    g -> getObjectInfo().outDynamicFn("sayHi");
    s -> getObjectInfo().outDynamicFn("sayHello");
    s -> getObjectInfo().outDynamicFn("sayHi");
    
    CPPUNIT_ASSERT(f -> getObjectInfo().getDynamicFn("sayHello") == null);
    CPPUNIT_ASSERT(g -> getObjectInfo().getDynamicFn("sayHello") == null);
    CPPUNIT_ASSERT(s -> getObjectInfo().getDynamicFn("sayHi") == null);
    
    delete f;
    delete s;
    delete g;
}
