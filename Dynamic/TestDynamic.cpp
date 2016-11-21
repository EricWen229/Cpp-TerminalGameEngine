#include "TestDynamic.h"

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TestDynamic, "TestDynamic");

TestDynamic::TestDynamic() {}
TestDynamic::~TestDynamic() {}

void TestDynamic::testGetClassName()
{
    Father::RegisterClassInfo();
    Son::RegisterClassInfo();
    GrandSon::RegisterClassInfo();
    
    Father *f =
        (Father *)ClassInfos().getClassInfo("Father")
        -> getConstructor()(null);
    Father *s =
        (Father *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null);
    Father *g =
        (Father *)ClassInfos().getClassInfo("GrandSon")
        -> getConstructor()(null);
        
    CPPUNIT_ASSERT(f -> getClassInfo().getName() == "Father");
    CPPUNIT_ASSERT(s -> getClassInfo().getName() == "Son");
    CPPUNIT_ASSERT(g -> getClassInfo().getName() == "GrandSon");
    
    delete f;
    delete s;
    delete g;
}

void TestDynamic::testGetClassConstructor()
{
    Father::RegisterClassInfo();
    Son::RegisterClassInfo();
    GrandSon::RegisterClassInfo();
    
    Father *f =
        (Father *)ClassInfos().getClassInfo("Father")
        -> getConstructor()(null);
    Father *s =
        (Father *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null);
    Father *g =
        (Father *)ClassInfos().getClassInfo("GrandSon")
        -> getConstructor()(null);
        
    CPPUNIT_ASSERT
    (f -> getClassInfo().getConstructor()
     == (ClassInfo::ConFn)Father::createObject);
    CPPUNIT_ASSERT
    (s -> getClassInfo().getConstructor()
     == (ClassInfo::ConFn)Son::createObject);
    CPPUNIT_ASSERT
    (g -> getClassInfo().getConstructor()
     == (ClassInfo::ConFn)GrandSon::createObject);
     
    Father *ff = (Father *)f -> getClassInfo().getConstructor()(null);
    Father *ss = (Father *)s -> getClassInfo().getConstructor()(null);
    Father *gg = (Father *)g -> getClassInfo().getConstructor()(null);
    
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
        -> getConstructor()(null);
    Father *s =
        (Father *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null);
    Father *g =
        (Father *)ClassInfos().getClassInfo("GrandSon")
        -> getConstructor()(null);
        
    f -> RegisterObjectInfo();
    g -> RegisterObjectInfo();
    s -> RegisterObjectInfo();
    
    CPPUNIT_ASSERT(f -> getObjectInfo().getDynamicFn("sayHello") != null);
    CPPUNIT_ASSERT(s -> getObjectInfo().getDynamicFn("sayHello") != null);
    CPPUNIT_ASSERT(g -> getObjectInfo().getDynamicFn("sayHi") != null);
    
    int a = 1;
    char b = 'z';
    void *arr[] = { (void *) &a, (void *) &b };
    f -> getObjectInfo().getDynamicFn("sayHello")((void *)arr);
    s -> getObjectInfo().getDynamicFn("sayHello")((void *)arr);
    g -> getObjectInfo().getDynamicFn("sayHi")((void *)arr);
    
    g -> getObjectInfo().regDynamicFn
    ("Test", [](void *)->void * {return null;});
    g -> getObjectInfo().getDynamicFn("Test")(null);
    
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
        -> getConstructor()(null);
    Father *s =
        (Father *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null);
    Father *g =
        (Father *)ClassInfos().getClassInfo("GrandSon")
        -> getConstructor()(null);
        
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

void TestDynamic::testGetObjectId()
{
    ObjectId id1 = GetObjectId()();
    ObjectId id2 = GetObjectId()();
    CPPUNIT_ASSERT(id1 == id2 - 1);
}

void TestDynamic::testRegObjectAndOutObject()
{
    Father::RegisterClassInfo();
    Son::RegisterClassInfo();
    GrandSon::RegisterClassInfo();
    
    Father *f =
        (Father *)ClassInfos().getClassInfo("Father")
        -> getConstructor()(null);
    Father *s =
        (Father *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null);
    Father *g =
        (Father *)ClassInfos().getClassInfo("GrandSon")
        -> getConstructor()(null);
        
    f -> RegisterObjectInfo();
    s -> RegisterObjectInfo();
    g -> RegisterObjectInfo();
    
    ObjectId fid = f -> objectId;
    ObjectId sid = s -> objectId;
    ObjectId gid = g -> objectId;
    
    CPPUNIT_ASSERT(ObjectInfos().getObjectInfo(fid) != null);
    CPPUNIT_ASSERT(ObjectInfos().getObjectInfo(sid) != null);
    CPPUNIT_ASSERT(ObjectInfos().getObjectInfo(gid) != null);
    
    delete f;
    delete s;
    delete g;
    
    CPPUNIT_ASSERT(ObjectInfos().getObjectInfo(fid) == null);
    CPPUNIT_ASSERT(ObjectInfos().getObjectInfo(sid) == null);
    CPPUNIT_ASSERT(ObjectInfos().getObjectInfo(gid) == null);
}

void TestDynamic::testGetDynamicFnByIdAndStr()
{
    Father::RegisterClassInfo();
    Son::RegisterClassInfo();
    GrandSon::RegisterClassInfo();
    
    Father *f =
        (Father *)ClassInfos().getClassInfo("Father")
        -> getConstructor()(null);
    Father *s =
        (Father *)ClassInfos().getClassInfo("Son")
        -> getConstructor()(null);
    Father *g =
        (Father *)ClassInfos().getClassInfo("GrandSon")
        -> getConstructor()(null);
        
    f -> RegisterObjectInfo();
    s -> RegisterObjectInfo();
    g -> RegisterObjectInfo();
    
    ObjectInfos().getObjectInfo(f -> objectId) -> getDynamicFn("sayHello")(null);
    auto p = ObjectInfos().getObjectInfo(s -> objectId);
    ObjectInfos().getObjectInfo(s -> objectId) -> getDynamicFn("sayHello")(null);
    ObjectInfos().getObjectInfo(g -> objectId) -> getDynamicFn("sayHi")(null);
    
    delete f;
    delete s;
    delete g;
}
