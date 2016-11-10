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
        
    private:
        int count;
        friend class SmartArray<T>;
        
    public:
        Array(int h, int w);
        ~Array();
        T get(int i, int j);
};

template <class T>
class SmartArray
{
    private:
        Array<T> *array;
        
    public:
        SmartArray(Array<T> *a);
        SmartArray(const SmartArray &sa);
        ~SmartArray();
        Array<T> *operator->();
};

template <class T>
SmartArray<T> createArray(int height, int width)
{
    Array<T> *a = new Array<T>(height, width);
    SmartArray<T> sa(a);
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
T Array<T>::get(int i, int j)
{
    assert(i >= 0 && i < height && j >= 0 && j < width);
    return array[i][j];
}

template <class T>
SmartArray<T>::SmartArray(Array<T> *a): array(a)
{
    array -> count++;
}

template <class T>
SmartArray<T>::SmartArray(const SmartArray &sa): array(sa.array)
{
    array -> count++;
}

template <class T>
SmartArray<T>::~SmartArray()
{
    array -> count--;
    if (array -> count == 0)
    {
        delete array;
    }
}

template <class T>
Array<T> *SmartArray<T>::operator->()
{
    return array;
}

#endif
