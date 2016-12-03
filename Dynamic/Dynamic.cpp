#include "Dynamic.h"

ObjectId GetObjectId::num = 0;

ObjectId GetObjectId::operator()()
{
    num++;
    return num;
}

ClassInfo::ClassInfo(const std::string &cn, ConFn &cfn):
    ClassName(cn), Constructor(cfn) {}

ClassInfo::~ClassInfo() {}

ObjectInfo::ObjectInfo() {}

ObjectInfo::~ObjectInfo() {}

void ObjectInfo::regDynamicFn(const std::string &funcName, const DynamicFn &fn)
{
    funsMap.insert(FunsMap::value_type(funcName, fn));
}

void ObjectInfo::outDynamicFn(const std::string &funcName)
{
    FunsMap::const_iterator it = funsMap.find(funcName);
    if (it != funsMap.end())
    {
        funsMap.erase(it);
    }
}

ObjectInfo::DynamicFn ObjectInfo::getDynamicFn(const std::string &funcName)
{
    FunsMap::const_iterator it = funsMap.find(funcName);
    if (it == funsMap.end())
    {
        return null;
    }
    else
    {
        return it -> second;
    }
}

std::map<const std::string, ClassInfo *> ClassInfos::infosMap;

ClassInfos::ClassInfos() {}

ClassInfos::~ClassInfos() {}

void ClassInfos::regClass(const std::string &className, ClassInfo *ci)
{
    infosMap.insert(InfosMap::value_type(className, ci));
}

void ClassInfos::outClass(const std::string &className)
{
    InfosMap::const_iterator it = infosMap.find(className);
    if (it != infosMap.end())
    {
        infosMap.erase(it);
    }
}

ClassInfo *ClassInfos::getClassInfo(const std::string &className)
{
    InfosMap::const_iterator it = infosMap.find(className);
    if (it == infosMap.end())
    {
        return null;
    }
    else
    {
        return it -> second;
    }
}

std::map<const ObjectId, ObjectInfo *> ObjectInfos::infosMap;

ObjectInfos::ObjectInfos() {}

ObjectInfos::~ObjectInfos() {}

void ObjectInfos::regObject(const ObjectId &id, ObjectInfo *ci)
{
    infosMap.insert(InfosMap::value_type(id, ci));
}

void ObjectInfos::outObject(const ObjectId &id)
{
    InfosMap::const_iterator it = infosMap.find(id);
    if (it != infosMap.end())
    {
        infosMap.erase(it);
    }
}

ObjectInfo *ObjectInfos::getObjectInfo(const ObjectId &id)
{
    InfosMap::const_iterator it = infosMap.find(id);
    if (it == infosMap.end())
    {
        return null;
    }
    else
    {
        return it -> second;
    }
}

Implement_Class(DynamicRootObject)

Implement_Object(DynamicRootObject)
{
    Register_Object(DynamicRootObject);
}

DynamicRootObject::DynamicRootObject():
    objectId(GetObjectId()()) {}

DynamicRootObject::~DynamicRootObject()
{
    Out_Object(DynamicRootObject);
}

DynamicRootObject *DynamicRootObject::createObject(void *unused)
{
    return new DynamicRootObject;
}
