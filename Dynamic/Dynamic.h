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
        ObjectInfo objectInfo; \
    public:  \
        const ObjectId objectId; \
    public: \
        static void RegisterClassInfo(); \
        virtual void RegisterObjectInfo(); \
        virtual ClassInfo &getClassInfo(); \
        virtual ObjectInfo &getObjectInfo();

#define Implement_Class(name) \
    ClassInfo name::classInfo((#name), (ClassInfo::ConFn)name::createObject); \
    void name::RegisterClassInfo() { ClassInfos().regClass(#name, &name::classInfo); } \
    ClassInfo &name::getClassInfo() { return classInfo; } \
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

class Object;

/* S represent Static */
class ClassInfo
{
    public:
        typedef void *(*ConFn)(void *);
        
    private:
        const std::string className;
        const ConFn constructorFn;
        
    public:
        ClassInfo(std::string cn, ConFn cfn);
        ~ClassInfo();
        
        const std::string &getName();
        ConFn getConstructor();
};

/* N represent Non-Static */
class ObjectInfo
{
    public:
        typedef std::function<void *(void *)> DynamicFn;
        
    private:
        typedef std::map<std::string, DynamicFn> FunsMap;
        FunsMap funsMap;
        
    public:
        ObjectInfo();
        ~ObjectInfo();
        
        void regDynamicFn(const std::string &funcName, DynamicFn fn);
        void outDynamicFn(const std::string &funcName);
        DynamicFn getDynamicFn(const std::string &funcName);
};

/* singleton */
class ClassInfos
{
    private:
        typedef std::map<std::string, ClassInfo *> InfosMap;
        static InfosMap infosMap;
        
    public:
        ClassInfos();
        ~ClassInfos();
        
        void regClass(const std::string &className, ClassInfo *ci);
        void outClass(const std::string &className);
        ClassInfo *getClassInfo(const std::string &className);
};

/* singleton */
class ObjectInfos
{
    private:
        typedef std::map<ObjectId, ObjectInfo *> InfosMap;
        static InfosMap infosMap;
        
    public:
        ObjectInfos();
        ~ObjectInfos();
        
        void regObject(ObjectId id, ObjectInfo *ci);
        void outObject(ObjectId id);
        ObjectInfo *getObjectInfo(ObjectId id);
};

#endif
