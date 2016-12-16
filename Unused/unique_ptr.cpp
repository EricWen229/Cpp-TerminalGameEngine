#include <memory>
#include <iostream>

std::unique_ptr<int> f(std::unique_ptr<int> &&p)
{
    return std::move(p);
}

int main()
{
    /* 对某些返回值无要求的函数，可以改成f的形式以适应unique_ptr */
    auto pInt = std::unique_ptr<int>(new int(5));
    pInt = f(std::move(pInt));
    std::cout << *pInt << std::endl;
    
    /* 资源所有权的转移 */
    auto pInt_ = std::move(pInt);
    pInt = std::move(pInt_);
    
    /* reset操作 */
    pInt.reset(new int(3));
    
    /* swap操作 */
    auto pA = std::unique_ptr<int>(new int(1));
    auto pB = std::unique_ptr<int>(new int(2));
    pA.swap(pB);
    std::cout << *pA << std::endl;
    std::cout << *pB << std::endl;
    
    /* release操作 */
    /* 释放之后就需要自己手动删除 */
    int *p = pInt.release();
    std::cout << *p << std::endl;
    delete p;
}
