#ifndef _PTR_WRAPPER_H_
#define _PTR_WRAPPER_H_

#include "../FirstLabUtility/Move.h"
#include <iostream>

template <typename T>
class PtrWrapper {

    T* ptr;

public:
    PtrWrapper() : ptr(nullptr) {}
    
    PtrWrapper(T* _ptr) : ptr(_ptr) {}

    PtrWrapper(const PtrWrapper&) = delete;

    PtrWrapper& operator=(const PtrWrapper&) = delete;

    PtrWrapper(PtrWrapper && other) noexcept {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    PtrWrapper& operator=(PtrWrapper && other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }

        return *this;
    }

    ~PtrWrapper() {
        delete ptr;
        std::cout << "\nTreeDeleted\n";
    }


    T* get() {
        return ptr;
    }

    T* release() {
        T* tmp = ptr;
        ptr = nullptr;
        return tmp;
    }

    void reset(T* _ptr = nullptr) {
        delete ptr;
        ptr = _ptr;
    }

    T* operator->() {
        return ptr;
    }

    const T* operator->() const {
        return ptr;
    }
  
    const T* get() const {
        return ptr;
    }

    T& operator*() {
        return *ptr;
    }

    const T& operator*() const {
        return *ptr;
    }

    explicit operator T*() const {
        return ptr;
    }

    
};


template <typename T>
class PtrWrapper<T[]> {

    T* ptr;

public:
    PtrWrapper() : ptr(nullptr) {}
    
    PtrWrapper(T* _ptr) : ptr(_ptr) {}

    PtrWrapper(const PtrWrapper&) = delete;

    PtrWrapper& operator=(const PtrWrapper&) = delete;

    PtrWrapper(PtrWrapper && other) noexcept {
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    PtrWrapper& operator=(PtrWrapper && other) noexcept {
        if (this != &other) {
            delete[] ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }

        return *this;
    }

    ~PtrWrapper() {
        delete[] ptr;
    }


    T* get() {
        return ptr;
    }

    T* release() {
        T* tmp = ptr;
        ptr = nullptr;
        return tmp;
    }

    void reset(T* _ptr = nullptr) {
        delete[] ptr;
        ptr = _ptr;
    }

  
    const T* get() const {
        return ptr;
    }

    T& operator*() {
        return *ptr;
    }

    const T& operator*() const {
        return *ptr;
    }

    explicit operator T*() const {
        return ptr;
    }

    T& operator[](size_t ind) {
        return *(ptr + ind);
    }

    const T& operator[](size_t ind)const  {
        return *(ptr + ind);
    }
};


template<typename T>
bool operator==(const PtrWrapper<T> &ptr_1, const PtrWrapper<T> &ptr_2) {
    return ptr_1.get() == ptr_2.get();
}

template<typename T>
bool operator==(const PtrWrapper<T> &ptr_1, std::nullptr_t) {
    return ptr_1.get() == nullptr;
}

template<typename T>
bool operator==(std::nullptr_t, const PtrWrapper<T> &ptr_2) {
    return ptr_2.get() == nullptr;
}

template<typename T>
bool operator!=(const PtrWrapper<T> &ptr_1, const PtrWrapper<T> &ptr_2) {
    return ptr_1.get() != ptr_2.get();
}

template<typename T>
bool operator!=(const PtrWrapper<T> &ptr_1, std::nullptr_t) {
    return ptr_1.get() != nullptr;
}

template<typename T>
bool operator!=(std::nullptr_t, const PtrWrapper<T> &ptr_2) {
    return ptr_2.get() != nullptr;
}



#endif