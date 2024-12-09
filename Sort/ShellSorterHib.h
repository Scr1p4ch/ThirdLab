#ifndef _SORT_SHELLSORTER_H_
#define _SORT_SHELLSORTER_H_
#include "Sorter.h"
#include "../Utility/Sequence.h"
#include "../FirstLabUtility/Move.h"
#include "../FirstLabUtility/Swap.h"


template <typename T>
class ShellSorterHib : public ISorter<T> {
public:
    ShellSorterHib() = default;

    ArraySequence<T>* Sort(ArraySequence<T> & arr, int (*cmp)(const T &, const T& )) override {
        ShellSort(arr, 0, arr.getSize() - 1, cmp);
        return &arr;
    }

    virtual ~ShellSorterHib() override = default;

private:
    void ShellSort(ArraySequence<T> & arr, int left, int right, int (*cmp)(const T &, const T &)) {
        int sz = right - left + 1;
        if (sz <= 1) return;

        int step = 1;
        while (step < sz) {
            step = step * 2 + 1;
        }

        int i, j, diff;
        while (step >= 1) {
            for (i = left + step; i <= right; ++i) {
                j = i;
                diff = j - step;
                while (diff >= left && cmp(arr[diff], arr[j]) > 0) {
                    MySwap(arr[diff], arr[j]);
                    j = diff;
                    diff = j - step;
                }
            }
            step /= 2;
        }
    }

};


#endif