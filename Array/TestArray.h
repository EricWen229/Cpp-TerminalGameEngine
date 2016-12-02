/* 1.空智能指针的默认构造函数，复制构造函数，赋值构造函数
 * 经过复制构造函数之后还是不是null
 * 经过赋值构造函数之后还是不是null */
/* 2.非空智能指针的构造函数，复制构造函数，赋值构造函数
 * 经过复制构造函数之后能不能指向同一块内存
 * 经过赋值构造函数之后能不能指向同一块内存 */
/* 3.非空智能指针在复制构造函数和赋值构造函数作用后
 * 原指针离开作用域被销毁，新指针能不能继续发挥作用 */
/* 4.非空智能指针被重新赋值，验证会不会导致内存泄漏
 * 重新赋值为空智能指针和非空智能指针都需要验证 */
/* 5.createArray(height, width)
 * 能否应对int,char等数据类型
 * 能否应对自定义的数据类型
 * 能否应对tuple，function等C++11的新数据类型 */
/* 6.createArray(top, ...)分配空间是否保证内存的一一对应性
 * 需要验证一次局部分配，两次局部分配，三次局部分配的情况
 * 要验证通过上一级指针的修改能不能反映在下一级指针上
 * 要验证通过下一级指针的修改能不能反映在上一级指针上
 * 特别关注在边界上的值 */

/* 1.testNull */
/* 2.testNoNull */
/* 3.testCopy
 * testAssign */
/* 4.testReAssign */
/* 5.testCreateArrayGlobal */
/* 6.testCreateArrayLocal */

#include <cppunit/extensions/HelperMacros.h>
#include "Array.h"

class TestArray: public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(TestArray);
        CPPUNIT_TEST(testPart);
        CPPUNIT_TEST(testShare);
        CPPUNIT_TEST(testNull);
        CPPUNIT_TEST(testReassign);
        CPPUNIT_TEST(testStatic);
        CPPUNIT_TEST_SUITE_END();
        
    public:
        TestArray();
        ~TestArray();
        void testPart();
        void testShare();
        void testNull();
        /* 看一看对同一个变量重新赋值会不会导致内存泄漏 */
        void testReassign();
        void testStatic();
};
