/* 1.Semaphore的计数器在大于等于0时，代表资源数 */
/* 2.Semaphore的计数器在小于0时，绝对值代表正在等待的进程或线程数 */
/* 3.Semaphore的计数器在小于0时，每加1都应该唤醒一个进程或者线程
 * 但这一点很难直接测试，折中的办法是让线程去修改一个变量
 * 然后检查这个变量的值是否符合预期 */
/* 4.测试两个资源在确定申请顺序之后是否可以避免死锁问题
 * 但这一点也很难测试，只能指定2个到4个线程同时运行
 * 并且设定线程沉睡时间（比如间隔1ms、2ms等），模拟抢占的情况
 * 同时设定每一个拿到资源的线程都沉睡5ms以模拟对资源的占有过程 */
/* 5.测试典型地生产者消费者问题是否会出现死锁（带临界区） */
/* 6.测试是否所有的拷贝构造和赋值构造函数都不能正常使用
 * 看编译期是否报错即可 */

/* 1.testSPositive */
/* 2.testSNegative */
/* 3.testWakeUp */
/* 4.testDeadlock */
/* 5.testProducerConsumer */
/* 6.testNoCopy */

#include <cppunit/extensions/HelperMacros.h>
#include "Semaphore.h"
#include <atomic>
#include <functional>
#include <unistd.h>

class TestSemaphore: public CppUnit::TestFixture
{
    private:
        CPPUNIT_TEST_SUITE(TestSemaphore);
        CPPUNIT_TEST(testSPositive);
        CPPUNIT_TEST(testSNegative);
        CPPUNIT_TEST(testWakeUp);
        CPPUNIT_TEST(testDeadlock);
        CPPUNIT_TEST(testProducerConsumer);
        CPPUNIT_TEST_SUITE_END();
        
    public:
        TestSemaphore();
        ~TestSemaphore();
        void testSPositive();
        void testSNegative();
        void testWakeUp();
        void testDeadlock();
        void testProducerConsumer();
        void testNoCopy();
};
