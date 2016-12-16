#include <memory>
#include <iostream>

void f(std::shared_ptr<int> p)
{
    (*p)++;
}

int *g()
{
    return std::shared_ptr<int>(new int(2)).get();
}

std::unique_ptr<int> h()
{
    return std::unique_ptr<int>(std::shared_ptr<int>(new int(2)).get());
}

int main()
{
    std::shared_ptr<int> pInt(new int(5));
    f(pInt);
    std::cout << *pInt << std::endl;
    
    /* reset操作 */
    pInt.reset(new int(3));
    std::cout << *pInt << std::endl;
    
    std::shared_ptr<int> pA(new int(1));
    std::shared_ptr<int> pB(new int(2));
    pA.swap(pB);
    std::cout << *pA << std::endl;
    std::cout << *pB << std::endl;
    
    /* 可以安全地转移资源的所有权，不会导致内存泄漏 */
    pB = std::move(pA);
    std::cout << *pB << std::endl;
    
    /* 从shared_ptr中取出指针并不需要手动释放之 */
    int *p = pB.get();
    std::cout << *p << std::endl;
    /* 这个特点是有可能带来问题的 */
    /* 从shared_ptr中提取出裸指针是一个危险的行为 */
    std::cout << *g() << std::endl;
    std::cout << *h() << std::endl;
}
