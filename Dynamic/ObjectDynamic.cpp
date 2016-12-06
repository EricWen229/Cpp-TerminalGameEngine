#include "ObjectDynamic.h"

ObjectId GetObjectId::num = 0;

ObjectId GetObjectId::operator()()
{
    num++;
    return num;
}

ObjectInfo::ObjectInfo() {}
ObjectInfo::~ObjectInfo() {}

void ObjectInfo::regDynamicFn(const std::string &funcName, DynamicFn fn)
{
    funsMap.insert(FunsMap::value_type(funcName, fn));
}

ObjectInfo::DynamicFn ObjectInfo::getDynamicFn(const std::string &funcName)
{
    FunsMap::const_iterator it = funsMap.find(funcName);
    if (it == funsMap.end())
    {
        return nullptr;
    }
    else
    {
        return it -> second;
    }
}

std::map<const ObjectId, ObjectInfo *const> ObjectInfos::infosMap;

ObjectInfos::ObjectInfos() {}
ObjectInfos::~ObjectInfos() {}

void ObjectInfos::regObject(const ObjectId &id, ObjectInfo *const ci)
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

ObjectInfo *const ObjectInfos::getObjectInfo(const ObjectId &id)
{
    InfosMap::const_iterator it = infosMap.find(id);
    if (it == infosMap.end())
    {
        return nullptr;
    }
    else
    {
        return it -> second;
    }
}

Implement_Object(DynamicRootObject)
{
    Register_Object(DynamicRootObject);
}

DynamicRootObject::DynamicRootObject():
    objectId(GetObjectId()())
{
    RegisterObjectInfo();
}

DynamicRootObject::DynamicRootObject(const ObjectId &id):
    objectId(id)
{
    RegisterObjectInfo();
}

DynamicRootObject::~DynamicRootObject()
{
    Out_Object(DynamicRootObject);
}
