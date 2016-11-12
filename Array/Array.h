#ifndef Array_H
#define Array_H

#include <assert.h>

#define null nullptr

template <class T>
class SmartArray;

template <class T>
class Array
{
    private:
        int height;
        int width;
        T **array;
        
        /* 如果是已分配Array的一部分，则不要释放内存 */
        bool part;
        
    private:
        int count;
        friend class SmartArray<T>;
        
    public:
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
        ~SmartArray();
        
        Array<T> *operator->();
        T *operator[](int i);
        bool isNull();
};

template <class T>
SmartArray<T> createArray(int height, int width)
{
    Array<T> *a = new Array<T>(height, width);
    SmartArray<T> sa(a);
    return sa;
}

template <class T>
SmartArray<T> createArray(int height, int width, T **a)
{
    Array<T> *b = new Array<T>(height, width, a);
    SmartArray<T> sa(b);
    return sa;
}

template <class T>
SmartArray<T> createArray(int top, int left, int height, int width, SmartArray<T> sa)
{
    T *arr[height];
    for (int i = 0; i < height; i++)
    {
        arr[i] = &sa[top + i][left];
    }
    return createArray(height, width, arr);
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
    height(h), width(w), array(a), part(true), count(0) {}

template <class T>
Array<T>::~Array()
{
    if (!part)
    {
        assert(count == 0);
        for (int i = 0; i < height; i++)
        {
            delete[] array[i];
        }
        delete[] array;
    }
}

template <class T>
SmartArray<T>::SmartArray(): array(null) {}

template <class T>
SmartArray<T>::SmartArray(Array<T> *a): array(a)
{
    assert(!isNull());
    array -> count++;
}

template <class T>
SmartArray<T>::SmartArray(const SmartArray &sa): array(sa.array)
{
    if (!isNull())
    {
        array -> count++;
    }
}

template <class T>
SmartArray<T>::~SmartArray()
{
    if (!isNull())
    {
        array -> count--;
        if (array -> count == 0)
        {
            delete array;
        }
    }
}

template <class T>
Array<T> *SmartArray<T>::operator->()
{
    assert(!isNull());
    return array;
}

template <class T>
T *SmartArray<T>::operator[](int i)
{
    assert(!isNull());
    assert(i >= 0 && i < array -> height);
    return array -> array[i];
}

template <class T>
bool SmartArray<T>::isNull()
{
    return array == null;
}

#endif
