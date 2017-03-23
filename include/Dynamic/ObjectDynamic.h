/* 为减轻软件开发的复杂度，ObjectDynamic只服务于Mailbox */
/* ObjectDynamic认为，如果用户可以直接拿到对象，就没有理由使用动态反射机制 */
/* 因此，ObjectDynamic也不服务于任何其他可以拿到对象的情况 */
/* 故在DynamicRootObject中，是没有getObjectInfo方法的 */
/* ObjectDynamic禁止任何动态注册的函数具有返回值，以方便实现 */
/* Dynamic缩减的重要原因也是，无法给出前件和后件断言，也非常难测试 */

#ifndef ObjectDynamic_H
#define ObjectDynamic_H

#include <functional>
#include <string>
#include <map>

typedef int ObjectId;

class GetObjectId
{
    private:
        static ObjectId num;
        
    public:
        ObjectId operator()();
};

#define Declare_Object \
    private: \
        virtual void RegisterObjectInfo();

#define Implement_Object(name) \
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

class ObjectInfo
{
    public:
        typedef const std::function<void(void *)> DynamicFn;
        
    private:
        typedef std::map<const std::string, DynamicFn> FunsMap;
        FunsMap funsMap;
        DynamicRootObject *object;
        
    public:
        ObjectInfo(DynamicRootObject *obj);
        ~ObjectInfo();
        
        DynamicFn getDynamicFn(const std::string &funcName);
        void regDynamicFn(const std::string &funcName, DynamicFn f);
        DynamicRootObject *getObject();
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
        Declare_Object;
        
    protected:
        ObjectInfo objectInfo;
        
    public:
        const ObjectId objectId;
        DynamicRootObject();
        DynamicRootObject(const ObjectId &id);
        virtual ~DynamicRootObject();
        void OutObjectInfo();
};

#endif
