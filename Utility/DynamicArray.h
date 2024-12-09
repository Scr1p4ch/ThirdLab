#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_

#include "PtrWrapper.h"

template <typename T>
class DynamicArray {

    int size;
    PtrWrapper<T[]> ptr;
    int current;

public:
    DynamicArray() : size(16), ptr(new T[size]), current(-1) {}

    DynamicArray(int _size) : size(_size), ptr(new T[size]), current(-1) {}

    DynamicArray(const DynamicArray & other) : size(other.size), ptr(new T[size]), current(other.current) {
        for (int i = 0; i < size; ++i) {
            ptr[i] = other.ptr[i];
        }
    } 

    ~DynamicArray() = default;

    T& operator[] (int idx) {
        if (idx >= size) {
            resize(idx);
        }
        if (current < idx) {
            current = idx;
        }

        return ptr[idx];
    }

    int getSize() const {
        return size;
    }

    int getCurrent() const {
        return current;
    }

    void resize(int _idx);

};


template <typename T>
void DynamicArray<T>::resize(int _idx) {
    int new_size = size;
    current = _idx;

    while (new_size <= _idx) {
        new_size *= 2;
    }

    T* new_ptr = new T[new_size];

    for (int i = 0; i < size; ++i) {
        new_ptr[i] = ptr[i];
    }
    ptr.reset(new_ptr);
    size = new_size;
}

#endif