#include "Dynamic.h"

ClassInfo_S::ClassInfo_S(std::string cn, ConFn cfn):
    className(cn), constructorFn(cfn) {}

ClassInfo_S::~ClassInfo_S() {}

const std::string &ClassInfo_S::getName()
{
    return className;
}

ClassInfo_S::ConFn ClassInfo_S::getConstructor()
{
    return constructorFn;
}

ClassInfo_N::ClassInfo_N() {}

ClassInfo_N::~ClassInfo_N() {}

void ClassInfo_N::regDynamicFn(const std::string &funcName, DynamicFn fn)
{
    funsMap.insert(FunsMap::value_type(funcName, fn));
}

void ClassInfo_N::outDynamicFn(const std::string &funcName)
{
    FunsMap::const_iterator it = funsMap.find(funcName);
    if (it != funsMap.end())
    {
        funsMap.erase(it);
    }
}

ClassInfo_N::DynamicFn ClassInfo_N::getDynamicFn(const std::string &funcName)
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

std::map<std::string, ClassInfo_S *> ClassInfos::infosMap;

ClassInfos::ClassInfos() {}

ClassInfos::~ClassInfos() {}

void ClassInfos::regClass(const std::string &className, ClassInfo_S *ci)
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

ClassInfo_S *ClassInfos::getClassInfo(const std::string &className)
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

Implement_Class(Object)
{
    Register_Fn(Object, run);
}

Object::Object() {}

Object::~Object()
{
}

Object *Object::createObject(void **unusedP, int unusedI)
{
    return new Object;
}

void *Object::run(void *unusedP, int unusedI)
{
    std::cout << "Hello!" << std::endl;
    std::cout << unusedI << std::endl;
    return null;
}
