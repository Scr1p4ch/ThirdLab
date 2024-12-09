#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "DynamicArray.h"
#include <stdexcept>

template <typename T>
class ArraySequence {
    DynamicArray<T> arr;

public:
    ArraySequence() = default;
    ArraySequence(int _size) : arr(_size) {}
    ArraySequence(int _size, T* _items) : arr(_size) {
        for (int i = 0; i < _size; ++i) {
            arr[i] = _items[i];
        }
    }

    ArraySequence(const ArraySequence & other) : arr(other.arr) {}

    ~ArraySequence() = default;

    ArraySequence<T>* concat(ArraySequence<T>* _arr) {
        int current = arr.getCurrent();
        int other_size = _arr->getSize();
        int n = current + other_size;

        for (int i = current; i < n; ++i) {
            this->append((*_arr)[i - current]);
        }
        return this;
    }

    T& getFirst() {
        if (0 == arr.getSize()) {
            throw std::out_of_range("ArraySequence::getFirst");
        }
        return arr[0];
    }

    T& getLast() {
        if (0 == arr.getSize()) {
            throw std::out_of_range("ArraySequence::getLast");
        }
        return arr[arr.getCurrent()];
    }

    int getSize() const {
        return arr.getSize();
    }

    T& operator[](int idx) {
        return arr[idx];
    }

    T operator[](int idx) const {
        return arr[idx];
    }

    /*const T& operator[](int idx) const {
        return arr[idx];
    }
    */

    void append(const T & elem) {
        arr[arr.getCurrent() + 1] = elem;
    }
    

    T& get(const size_t idx) {
        return arr[idx];
    }

    int getCurrent() {
        return arr.getCurrent();
    }

    void Swap(size_t idx_1, size_t idx_2) {
        T tmp = Move(arr[idx_1]);
        arr[idx_1] = Move(arr[idx_2]);
        arr[idx_2] = Move(tmp);
    }
};



#endif