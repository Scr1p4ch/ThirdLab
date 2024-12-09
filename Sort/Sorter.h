#ifndef _SORT_SORTER_H_
#define _SORT_SORTER_H_

#include "../Utility/Sequence.h"

template <typename T>
class Sorter {
public:
    virtual ~Sorter() = default;

    virtual ArraySequence<T>* Sort(ArraySequence<T>* arr, int (*cmp)(const T & , const T & )) = 0;
};

template <typename T>
class ISorter {
public:
    virtual ~ISorter() = default;

    virtual ArraySequence<T>* Sort(ArraySequence<T>& arr, int (*cmp)(const T & , const T & )) = 0;
};




#endif