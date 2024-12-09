#ifndef _SORT_QUICKSORTER_H_
#define _SORT_QUICKSORTER_H_

#include "Sorter.h"
//#include "InsertionSort.h"
#include "../Utility/Sequence.h"
#include "../FirstLabUtility/Move.h"
#include "../FirstLabUtility/Swap.h"


template <typename T>
class QuickSorter : public ISorter<T> {
public:
    QuickSorter() = default;

    ArraySequence<T>* Sort(ArraySequence<T> & arr, int (*cmp)(const T &, const T& )) override {
        QuickSort(arr, 0,  arr.getSize() - 1, cmp);
        return &arr;
    }

    virtual ~QuickSorter() override = default;

private:
    void QuickSort(ArraySequence<T> & arr, int low, int high, int (*cmp)(const T& , const T& )) {
            if (high - low <= 32) {
                for (int i = low + 1; i <= high; ++i) {
                    int j = i - 1;
                    while (j >= 0 && 1 == cmp(arr[j], arr[j + 1])) {
                        std::swap(arr[j], arr[j + 1]);
                        --j;
                    }
                }
                return;
            }
            int i = Partition(arr, low, high, cmp);
            QuickSort(arr, low, i, cmp);
            QuickSort(arr, i + 1, high, cmp);

            
    }

    inline int Partition(ArraySequence<T>& arr, int l, int h, int (*cmp)(const T &, const T &)) {
        int index = (l + h) / 2;
        T v = arr[index];
        int i = l;
        int j = h;

        while (i <= j) {
            while (-1 == cmp(arr[i], v)) {
                ++i;
            }
            while (1 == cmp(arr[j], v))
            {
                --j;
            }
            if (i >= j) {
                break;
            }
            
            std::swap(arr[i++], arr[j--]);
            //MySwap(arr[i++], arr[j--]);
        }
        return j;
    }
};


/*
template <typename T>
class QuickSorter : public Sorter<T> {
public:
    QuickSorter() = default;

    ArraySequence<T>* Sort(ArraySequence<T>* arr, int (*cmp)(const T &, const T& )) override {
        QuickSort(arr, 0,  arr->getSize() - 1, cmp);
        return arr;
    }

    virtual ~QuickSorter() override = default;

private:
    void QuickSort(ArraySequence<T>* arr, int low, int high, int (*cmp)(const T& , const T& )) {
        
        while (low < high) {
            if (high - low <= 32) {
                for (int i = low + 1; i <= high; ++i) {
                    int j = i - 1;
                    while (j >= 0 && 1 == cmp((*arr)[j], (*arr)[j + 1])) {
                        std::swap((*arr)[j], (*arr)[j + 1]);
                        --j;
                    }
                }
                return;
            }
            int i = Partition(arr, low, high, cmp);
            //QuickSort(arr, low, i, cmp);
            //QuickSort(arr, i + 1, high, cmp);

            if (i - low < high - i) {
                QuickSort(arr, low, i, cmp);
                low = i + 1;
            }
            else {
                QuickSort(arr, i + 1, high, cmp);
                high = i;
            }
        }
    }

    inline int Partition(ArraySequence<T>* arr, int l, int h, int (*cmp)(const T &, const T &)) {
        T v = (*arr)[(l + h) / 2];
        int i = l;
        int j = h;

        while (i <= j) {
            while (-1 == cmp((*arr)[i], v)) {
                ++i;
            }
            while (1 == cmp((*arr)[j], v))
            {
                --j;
            }
            if (i >= j) {
                break;
            }
            
            //std::swap((*arr)[i++], (*arr)[j--]);
            MySwap((*arr)[i++], (*arr)[j--]);
        }
        return j;
    }
};*/

#endif