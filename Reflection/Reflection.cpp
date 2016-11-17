#include "Reflection.h"

static std::map<std::string, ClassInfo *> *classInfoMap = NULL;

bool Register(ClassInfo *ci)
{
    return Object::Register(ci);
}

ClassInfo::ClassInfo(const std::string className, ObjectConstructorFn ctor)
    :m_className(className) ,m_objectConstructor(ctor)
{
    Register(this);
}

ClassInfo::~ClassInfo() {}

Object *ClassInfo::CreateObject() const
{
    return m_objectConstructor ? (*m_objectConstructor)() : null;
}

bool ClassInfo::IsDynamic()const
{
    return null != m_objectConstructor;
}

const std::string ClassInfo::GetClassName() const
{
    return m_className;
}

ObjectConstructorFn ClassInfo::GetConstructor() const
{
    return m_objectConstructor;
}

IMPLEMENT_CLASS(Object)

bool Object::Register(ClassInfo *ci)
{
    if (!classInfoMap)
    {
        classInfoMap = new std::map<std::string, ClassInfo *>();
    }
    if (ci)
    {
        if (classInfoMap -> find(ci -> m_className) == classInfoMap -> end())
        {
            classInfoMap -> insert
            (std::map<std::string, ClassInfo *>::value_type(ci->m_className, ci));
        }
    }
    return true;
}

Object *Object::CreateObject(std::string name)
{
    std::map<std::string, ClassInfo *>::const_iterator iter =
        classInfoMap -> find(name);
    if (classInfoMap -> end() != iter)
    {
        return iter -> second -> CreateObject();
    }
    return null;
}
