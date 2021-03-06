#ifndef Array_H
#define Array_H

#include "../DiagHelper.h"
#include "../Semaphore/Semaphore.h"
#include "../DiagHelper.h"

#define null nullptr

template <class T>
class SmartArray;

template <class T>
class Array
{
    private:
        T **array;
        /* 如果是已分配Array的一部分，则不要释放内存 */
        bool part;
        
    private:
        int count;
        friend class SmartArray<T>;
        
    public:
        const int height;
        const int width;
        
        Array(int h, int w);
        Array(int h, int w, T **a);
        ~Array();
};

template <class T>
class SmartArray
{
    private:
        Array<T> *array;
        
    public:
        /* 为方便智能指针的定义 */
        SmartArray();
        SmartArray(Array<T> *a);
        SmartArray(const SmartArray &sa);
        SmartArray &operator=(const SmartArray &sa);
        ~SmartArray();
        
        Array<T> *operator->();
        T *operator[](int i);
        bool isNull() const;
};

template <class T>
SmartArray<T> createArray(int height, int width)
{
    Assert(height > 0 && width > 0);
    
    Array<T> *a = new Array<T>(height, width);
    SmartArray<T> sa(a);
    
    Assert(sa -> height == height);
    Assert(sa -> width == width);
    Assert(sa.isNull() == false);
    ExtraRun
    (
        for (int i = 0; i < height; i++)
        Assert(&sa[0][0] != nullptr);
    );
    return sa;
}

template <class T>
SmartArray<T> createArray(int height, int width, T **a)
{
    Assert(height > 0 && width > 0);
    ExtraRun
    (
        for (int i = 0; i < height; i++)
        Assert(a[i] != nullptr);
    );
    
    Array<T> *b = new Array<T>(height, width, a);
    SmartArray<T> sa(b);
    
    Assert(sa -> height == height && sa -> width == width);
    ExtraRun
    (for (int i = 0; i < height; i++)
     for (int j = 0; j < width; j++) Assert(&sa[i][j] == &a[i][j]););
    return sa;
}

template <class T>
SmartArray<T> createArray(int top, int left, int height, int width, SmartArray<T> sa)
{
    Assert(height > 0 && width > 0);
    Assert(top >= 0 && left >= 0);
    Assert(top + height <= sa -> height && left + width <= sa -> width);
    Assert(sa.isNull() == false);
    
    T **arr = new T*[height];
    for (int i = 0; i < height; i++)
    {
        arr[i] = &sa[top + i][left];
    }
    SmartArray<T> sb = createArray(height, width, arr);
    
    ExtraRun
    (
        for (int i = 0; i < height; i++)
        Assert(&sb[i][0] == &sa[top + i][left]);
    );
    Assert(sb -> height == height);
    Assert(sb -> width == width);
    return sb;
}

template <class T>
Array<T>::Array(int h, int w): height(h), width(w), part(false), count(0)
{
    array = new T*[height];
    for (int i = 0; i < height; i++)
    {
        array[i] = new T[width];
    }
}

template <class T>
Array<T>::Array(int h, int w, T **a):
    height(h), width(w), array(a), part(true), count(0)
{
}

template <class T>
Array<T>::~Array()
{
    Assert(count == 0);
    
    if (!part)
    {
        for (int i = 0; i < height; i++)
        {
            delete[] array[i];
        }
    }
    delete[] array;
}

template <class T>
SmartArray<T>::SmartArray(): array(null)
{
    Assert(isNull() == true);
}

template <class T>
SmartArray<T>::SmartArray(Array<T> *a): array(a)
{
    Assert(!isNull());
    
    array -> count++;
    
    ExtraRun
    (
        for (int i = 0; i < array -> height; i++)
        Assert((*this)[i] == a -> array[i]);
    );
    Assert((*this) -> height == a -> height);
    Assert((*this) -> width == a -> width);
}

template <class T>
SmartArray<T>::SmartArray(const SmartArray<T> &sa): array(sa.array)
{
    /* no pre-condition */
    
    if (!isNull())
    {
        array -> count++;
        
        /* 因为传入的是一个const引用，所以不能调用->方法 */
        ExtraRun
        (
            for (int i = 0; i < (*this) -> height; i++)
            Assert((*this)[i] == sa.array -> array[i]);
        );
        Assert((*this) -> height == sa.array -> height);
        Assert((*this) -> width == sa.array -> width);
    }
    Assert(isNull() == sa.isNull());
}

template <class T>
SmartArray<T> &SmartArray<T>::operator=(const SmartArray<T> &sa)
{
    /* no pre-condition */
    
    if (this == &sa)
    {
        return *this;
    }
    if (!isNull())
    {
        array -> count--;
        if (array -> count == 0)
        {
            delete array;
        }
    }
    if (!sa.isNull())
    {
        sa.array -> count++;
    }
    array = sa.array;
    
    /* hard to write a post-condition */
}

template <class T>
SmartArray<T>::~SmartArray()
{
    /* no pre-conditon */
    
    if (!isNull())
    {
        array -> count--;
        if (array -> count == 0)
        {
            delete array;
            array = nullptr;
        }
    }
    
    /* hard to write a post-condition */
}

template <class T>
Array<T> *SmartArray<T>::operator->()
{
    Assert(!isNull());
    
    Assert(array != nullptr);
    return array;
}

template <class T>
T *SmartArray<T>::operator[](int i)
{
    Assert(!isNull());
    Assert(i >= 0 && i < array -> height);
    
    Assert(array -> array[i] != nullptr);
    return array -> array[i];
}

template <class T>
bool SmartArray<T>::isNull() const
{
    return array == null;
}

#endif
