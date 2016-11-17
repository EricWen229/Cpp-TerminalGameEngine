#include "Dynamic.h"

ClassInfo::ClassInfo(std::string cn, ConFn cfn):
    className(cn), constructorFn(cfn) {}

ClassInfo::~ClassInfo() {}

const std::string &ClassInfo::getName()
{
    return className;
}

ClassInfo::ConFn ClassInfo::getConstructor()
{
    return constructorFn;
}

void ClassInfo::regDynamicFn(const std::string &funcName, DynamicFn fn)
{
    funsMap.insert(FunsMap::value_type(funcName, fn));
}

void ClassInfo::outDynamicFn(const std::string &funcName)
{
    FunsMap::const_iterator it = funsMap.find(funcName);
    if (it != funsMap.end())
    {
        funsMap.erase(it);
    }
}

ClassInfo::DynamicFn ClassInfo::getDynamicFn(const std::string &funcName)
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

std::map<std::string, ClassInfo *> ClassInfos::infosMap;

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

ClassInfo *ClassInfos::getClass(const std::string &className)
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

ClassInfo Object::classInfo("Object", Object::createObject);
ClassInfos().reg("Object", &Object::classInfo);

Object::Object() {}

Object::~Object() {}

Object *Object::createObject(void **unusedP, int unusedI)
{
    return new Object;
}

void Object::init()
{
    classInfo.regDynamicFn
    ("run",std::bind
     (&Object::run,
      this,
      std::placeholders::_1,
      std::placeholders::_2));
}

void *Object::run(void **unusedP, int unusedI)
{
    std::cout << "Hello!" << std::endl;
    return null;
}
