#include <functional>
#include <string>
#include <map>
#include <iostream>

#define null nullptr

#define Declare_Class \
    protected: \
        static ClassInfo_S classInfo_s; \
        ClassInfo_N classInfo_n; \
    public:  \
        virtual ClassInfo_S &getClassInfo_S(); \
        virtual ClassInfo_N &getClassInfo_N();

#define Implement_Class(name) \
    ClassInfo_S name::classInfo_s((#name), name::createObject); \
    ClassInfo_S &name::getClassInfo_S() { return classInfo_s; } \
    ClassInfo_N &name::getClassInfo_N() { return classInfo_n; }

#define Register_Fn(name) \
    classInfo_n.regDynamicFn \
    (#name,std::bind \
     (&Object::name, \
      this, \
      std::placeholders::_1, \
      std::placeholders::_2));

#define Register_Class(name) \
    void name::RegisterInfos()

class Object;

/* S represent Static */
class ClassInfo_S
{
    public:
        typedef Object *(*ConFn)(void **, int);
        
    private:
        const std::string className;
        const ConFn constructorFn;
        
    public:
        ClassInfo_S(std::string cn, ConFn cfn);
        ~ClassInfo_S();
        
        const std::string &getName();
        ConFn getConstructor();
};

/* N represent Non-Static */
class ClassInfo_N
{
    public:
        typedef std::function<void *(void **, int)> DynamicFn;
        
    private:
        const std::string className;
        typedef std::map<std::string, DynamicFn> FunsMap;
        FunsMap funsMap;
        
    public:
        ClassInfo_N();
        ~ClassInfo_N();
        
        void regDynamicFn(const std::string &funcName, DynamicFn fn);
        void outDynamicFn(const std::string &funcName);
        DynamicFn getDynamicFn(const std::string &funcName);
};

class ClassInfos
{
    private:
        typedef std::map<std::string, ClassInfo_S *> InfosMap;
        static InfosMap infosMap;
        
    public:
        ClassInfos();
        ~ClassInfos();
        
        void regClass(const std::string &className, ClassInfo_S *ci);
        void outClass(const std::string &className);
        ClassInfo_S *getClassInfo(const std::string &className);
};

class Object
{
    public:
        static ClassInfo_S classInfo_s;
        ClassInfo_N classInfo_n;
        
    public:
        Object();
        virtual ~Object();
        void RegisterInfos();
        
        static Object *createObject(void **unusedP = null, int unusedI = 0);
        void *run(void **unusedP = null, int unusedI = 0);
        ClassInfo_S &getClassInfo_S();
        ClassInfo_N &getClassInfo_N();
};
