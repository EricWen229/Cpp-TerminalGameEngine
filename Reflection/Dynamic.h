#include <functional>
#include <string>
#include <map>
#include <iostream>

#define null nullptr

class Object;
class ClassInfo
{
    public:
        typedef Object *(*ConFn)(void **, int);
        typedef std::function<void *(void **, int)> DynamicFn;
        /* typedef std::function<void *(int)> DynamicFn; */
        
    private:
        const std::string className;
        const ConFn constructorFn;
        typedef std::map<std::string, DynamicFn> FunsMap;
        FunsMap funsMap;
        
    public:
        ClassInfo(std::string cn, ConFn cfn);
        ~ClassInfo();
        
        const std::string &getName();
        ConFn getConstructor();
        void regDynamicFn(const std::string &funcName, DynamicFn fn);
        void outDynamicFn(const std::string &funcName);
        DynamicFn getDynamicFn(const std::string &funcName);
};

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
        ClassInfo *getClass(const std::string &className);
};

class Object
{
    public:
        static ClassInfo classInfo;
        
    public:
        Object();
        virtual ~Object();
        
        static Object *createObject(void **unusedP = null, int unusedI = 0);
        void *run(void **unusedP = null, int unusedI = 0);
        void init();
};
