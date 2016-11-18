#include "TestDynamic.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestDynamic, "TestDynamic");

TestDynamic::TestDynamic() {}
TestDynamic::~TestDynamic() {}

void TestDynamic::testGetName_S()
{
    Father::RegisterInfo_S();
    Son::RegisterInfo_S();
    GrandSon::RegisterInfo_S();
    
    Father *f =
        (Father *)ClassInfos().getClassInfo("Father")
        -> getConstructor()(null, 0);
    Father *s =
        (Father *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null, 0);
    Father *g =
        (Father *)ClassInfos().getClassInfo("GrandSon")
        -> getConstructor()(null, 0);
        
    CPPUNIT_ASSERT(f -> getClassInfo_S().getName() == "Father");
    CPPUNIT_ASSERT(s -> getClassInfo_S().getName() == "Son");
    CPPUNIT_ASSERT(g -> getClassInfo_S().getName() == "GrandSon");
    
    delete f;
    delete s;
    delete g;
}

void TestDynamic::testGetContructor_S()
{
    Father::RegisterInfo_S();
    Son::RegisterInfo_S();
    GrandSon::RegisterInfo_S();
    
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
    (f -> getClassInfo_S().getConstructor()
     == (ClassInfo_S::ConFn)Father::createObject);
    CPPUNIT_ASSERT
    (s -> getClassInfo_S().getConstructor()
     == (ClassInfo_S::ConFn)Son::createObject);
    CPPUNIT_ASSERT
    (g -> getClassInfo_S().getConstructor()
     == (ClassInfo_S::ConFn)GrandSon::createObject);
     
    Father *ff = (Father *)f -> getClassInfo_S().getConstructor()(null, 0);
    Father *ss = (Father *)s -> getClassInfo_S().getConstructor()(null, 0);
    Father *gg = (Father *)g -> getClassInfo_S().getConstructor()(null, 0);
    
    CPPUNIT_ASSERT(ff -> getClassInfo_S().getName() == "Father");
    CPPUNIT_ASSERT(ss -> getClassInfo_S().getName() == "Son");
    CPPUNIT_ASSERT(gg -> getClassInfo_S().getName() == "GrandSon");
    
    delete f;
    delete s;
    delete g;
    
    delete ff;
    delete ss;
    delete gg;
}

void TestDynamic::testRegClass()
{
    Father::RegisterInfo_S();
    CPPUNIT_ASSERT(ClassInfos().getClassInfo("Father") != null);
}

void TestDynamic::testOutClass()
{
    Father::RegisterInfo_S();
    ClassInfos().outClass("Father");
    CPPUNIT_ASSERT(ClassInfos().getClassInfo("Father") == null);
}

void TestDynamic::testRegDynamicFn()
{
    Father::RegisterInfo_S();
    Son::RegisterInfo_S();
    GrandSon::RegisterInfo_S();
    
    Father *f =
        (Father *)ClassInfos().getClassInfo("Father")
        -> getConstructor()(null, 0);
    Father *s =
        (Father *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null, 0);
    Father *g =
        (Father *)ClassInfos().getClassInfo("GrandSon")
        -> getConstructor()(null, 0);
        
    CPPUNIT_ASSERT(f -> getClassInfo_N().getDynamicFn("sayHello") != null);
    CPPUNIT_ASSERT(g -> getClassInfo_N().getDynamicFn("sayHello") != null);
    CPPUNIT_ASSERT(s -> getClassInfo_N().getDynamicFn("sayHi") != null);
    
    int arr[] = { 1 };
    f -> getClassInfo_N().getDynamicFn("sayHello")((void *)arr, 1);
    g -> getClassInfo_N().getDynamicFn("sayHello")((void *)arr, 1);
    s -> getClassInfo_N().getDynamicFn("sayHi")((void *)arr, 1);
    
    g -> getClassInfo_N().regDynamicFn
    ("Test", [](void *, int)->void * {return null;});
    g -> getClassInfo_N().getDynamicFn("Test")(null, 0);
    
    delete f;
    delete s;
    delete g;
}

void TestDynamic::testOutDynamicFn()
{
    Father::RegisterInfo_S();
    Son::RegisterInfo_S();
    GrandSon::RegisterInfo_S();
    
    Father *f =
        (Father *)ClassInfos().getClassInfo("Father")
        -> getConstructor()(null, 0);
    Father *s =
        (Father *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null, 0);
    Father *g =
        (Father *)ClassInfos().getClassInfo("GrandSon")
        -> getConstructor()(null, 0);
        
    f -> getClassInfo_N().outDynamicFn("sayHello");
    f -> getClassInfo_N().outDynamicFn("sayHi");
    g -> getClassInfo_N().outDynamicFn("sayHello");
    g -> getClassInfo_N().outDynamicFn("sayHi");
    s -> getClassInfo_N().outDynamicFn("sayHello");
    s -> getClassInfo_N().outDynamicFn("sayHi");
    
    CPPUNIT_ASSERT(f -> getClassInfo_N().getDynamicFn("sayHello") == null);
    CPPUNIT_ASSERT(g -> getClassInfo_N().getDynamicFn("sayHello") == null);
    CPPUNIT_ASSERT(s -> getClassInfo_N().getDynamicFn("sayHi") == null);
    
    delete f;
    delete s;
    delete g;
}
