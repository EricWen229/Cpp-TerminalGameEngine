#ifndef Array_H
#define Array_H

#include <assert.h>
#include <iostream>

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
        /* 如果持有的是已分配内存的某一部分，不必释放 */
        bool part;
        Array<T> *array;
        
    public:
        /* 为方便智能指针的定义 */
        SmartArray();
        SmartArray(Array<T> *a, bool p = false);
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
    SmartArray<T> sa(b, true);
    return sa;
}

template <class T>
Array<T>::Array(int h, int w): height(h), width(w), count(0)
{
    array = new T*[height];
    for (int i = 0; i < height; i++)
    {
        array[i] = new T[width];
    }
}

template <class T>
Array<T>::Array(int h, int w, T **a): height(h), width(w), array(a), count(0) {}

template <class T>
Array<T>::~Array()
{
    assert(count == 0);
    for (int i = 0; i < height; i++)
    {
        delete[] array[i];
    }
    delete[] array;
}

template <class T>
SmartArray<T>::SmartArray(): array(null), part(false) {}

template <class T>
SmartArray<T>::SmartArray(Array<T> *a, bool p): array(a), part(p)
{
    assert(array != null);
    array -> count++;
}

template <class T>
SmartArray<T>::SmartArray(const SmartArray &sa): array(sa.array)
{
    if (array != null && !part)
    {
        array -> count++;
    }
}

template <class T>
SmartArray<T>::~SmartArray()
{
    if (array == null || part)
    {
        return;
    }
    
    array -> count--;
    if (array -> count == 0)
    {
        delete array;
    }
}

template <class T>
Array<T> *SmartArray<T>::operator->()
{
    assert(array != null);
    return array;
}

template <class T>
T *SmartArray<T>::operator[](int i)
{
    assert(array != null);
    return array -> array[i];
}

template <class T>
bool SmartArray<T>::isNull()
{
    return array == null;
}

#endif
