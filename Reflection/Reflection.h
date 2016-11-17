#ifndef Reflection_H
#define Reflection_H

#include <string>
#include <map>

#define null NULL

class Object;
class ClassInfo;

bool Register(ClassInfo *ci);

class ClassInfo
{
    public:
        typedef Object *(*ObjectConstructorFn)();
        typedef void *(Object::*DynamicFn)();
        
    private:
        std::string m_className;
        ObjectConstructorFn m_objectConstructor;
        friend class Object;
        
    public:
        ClassInfo(const std::string className, ObjectConstructorFn ctor);
        virtual ~ClassInfo();
        
        Object *CreateObject() const;
        std::string GetClassName() const;
};

#define DECLARE_CLASS(name) \
    protected: \
        static ClassInfo ms_classinfo; \
    public:  \
        virtual ClassInfo* GetClassInfo() const; \
        static Object* CreateObject();

#define IMPLEMENT_CLASS_COMMON(name, func) \
    ClassInfo name::ms_classinfo((#name), \
             (ObjectConstructorFn) func); \
                          \
    ClassInfo *name::GetClassInfo() const \
        { return &name::ms_classinfo; }

#define IMPLEMENT_CLASS(name)            \
    IMPLEMENT_CLASS_COMMON(name, name::CreateObject) \
    Object* name::CreateObject()                   \
        { return new name; }


class Object
{
        DECLARE_CLASS(Object)
    public:
        Object() {}
        virtual ~Object() {}
        
        static bool Register(ClassInfo *ci);
        static Object *CreateObject(std::string name);
};

#endif
