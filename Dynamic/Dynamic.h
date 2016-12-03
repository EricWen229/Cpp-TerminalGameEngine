#ifndef Dynamic_H
#define Dynamic_H

#include <functional>
#include <string>
#include <map>
#include <iostream>

#define null nullptr

typedef int ObjectId;

class GetObjectId
{
    private:
        static ObjectId num;
        
    public:
        ObjectId operator()();
};

#define Declare_Class \
    protected: \
        static ClassInfo classInfo; \
    public: \
        static void RegisterClassInfo(); \
        static void OutClassInfo(); \
        virtual ClassInfo &getClassInfo();

#define Declare_Object \
    public: \
        virtual void RegisterObjectInfo(); \
        virtual void OutObjectInfo(); \
        virtual ObjectInfo &getObjectInfo();

#define Implement_Class(name) \
    ClassInfo name::classInfo((#name), \
    (std::function<DynamicRootObject*(void*)>)name::createObject); \
    void name::RegisterClassInfo() { ClassInfos().regClass(#name, &name::classInfo); } \
    void name::OutClassInfo() { ClassInfos().outClass(#name); } \
    ClassInfo &name::getClassInfo() { return classInfo; }

#define Implement_Object(name) \
    void name::OutObjectInfo() { ObjectInfos().outObject(objectId); } \
    ObjectInfo &name::getObjectInfo() { return objectInfo; } \
    void name::RegisterObjectInfo()

#define Register_Fn(className, funcName) \
    objectInfo.regDynamicFn \
    (#funcName, std::bind \
     (&className::funcName, \
      this, \
      std::placeholders::_1));

#define Register_Object(className) \
    ObjectInfos().regObject(objectId, &objectInfo);

#define Out_Object(className) \
    ObjectInfos().outObject(objectId);

class DynamicRootObject;

class ClassInfo
{
    public:
        typedef const std::function<DynamicRootObject*(void *)> ConFn;
        const std::string ClassName;
        ConFn Constructor;
        
    public:
        ClassInfo(const std::string &cn, ConFn &cfn);
        ~ClassInfo();
};

class ObjectInfo
{
    public:
        typedef const std::function<void *(void *)> DynamicFn;
        
    private:
        typedef std::map<const std::string, DynamicFn> FunsMap;
        FunsMap funsMap;
        
    public:
        ObjectInfo();
        ~ObjectInfo();
        
        void regDynamicFn(const std::string &funcName, const DynamicFn &fn);
        void outDynamicFn(const std::string &funcName);
        DynamicFn getDynamicFn(const std::string &funcName);
};

/* singleton */
class ClassInfos
{
    private:
        typedef std::map<const std::string, ClassInfo *const> InfosMap;
        static InfosMap infosMap;
        
    public:
        ClassInfos();
        ~ClassInfos();
        
        void regClass(const std::string &className, ClassInfo *const ci);
        void outClass(const std::string &className);
        ClassInfo *const getClassInfo(const std::string &className);
};

/* singleton */
class ObjectInfos
{
    private:
        typedef std::map<const ObjectId, ObjectInfo *const> InfosMap;
        static InfosMap infosMap;
        
    public:
        ObjectInfos();
        ~ObjectInfos();
        
        void regObject(const ObjectId &id, ObjectInfo *const ci);
        void outObject(const ObjectId &id);
        ObjectInfo *const getObjectInfo(const ObjectId &id);
};

/* 如果要使用根据id和成员函数名调用成员函数，继承体系上必须有它作为父类 */
/* 且不要多次继承 */
class DynamicRootObject
{
        Declare_Class;
        Declare_Object;
        
    protected:
        ObjectInfo objectInfo;
        
    public:
        const ObjectId objectId;
        DynamicRootObject();
        DynamicRootObject(const ObjectId &id);
        virtual ~DynamicRootObject();
        static DynamicRootObject *createObject(void *unused);
};

#endif
