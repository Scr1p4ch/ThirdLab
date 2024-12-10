#ifndef _TREES_BTREEBUILDER_HPP_
#define _TREES_BTREEBUILDER_HPP_

#include "../Utility/Sequence.h"
#include "../Sort/QuickSorter.h"
#include "../Utility/PtrWrapper.h"
#include "bTree.hpp"
#include "bTreeForDict.hpp"
#include "TypeFunctor.hpp"


template <typename T>
struct bTreeBuilder {
    PtrWrapper<BTree<T>> operator()(unsigned int t, ArraySequence<T>& arr, int (*cmp)(const T&, const T&)) {

        QuickSorter<T> qSort;

        ArraySequence<T>* a = qSort.Sort(arr, cmp);

        BTree<T>* treeToReturn = new BTree<T>(t, cmp);

        for (int i = 0; i < arr.getSize(); ++i) {
            treeToReturn->insert(a->get(i));
        }

        return PtrWrapper<BTree<T>>(treeToReturn);
    }

    PtrWrapper<BTree<T>> operator()(unsigned int t, T* elems, int (*cmp)(const T&, const T&), size_t size) {
        ArraySequence<T> arr(size, elems);

        QuickSorter<T> qSort;

        ArraySequence<T>* a = qSort.Sort(arr, cmp);

        BTree<T>* treeToReturn = new BTree<T>(t, cmp);

        for (int i = 0; i < arr.getSize(); ++i) {
            treeToReturn->insert(a->get(i));
        }

        return PtrWrapper<BTree<T>>(treeToReturn);
    }
};

/*
template <typename TKey, typename TElement>
struct bTreeBuilderForDict {
    PtrWrapper<bTreeForDict<TKey, TElement>> operator()(ArraySequence<TElement>& arr, unsigned int t, std::function<int(const TKey&, const TKey&)> compare = TypeFunctor<TKey>{}) {
        auto treeToReturn = new bTreeForDict<TKey, TElement>(t, compare);
        for (int i = 0; i < arr.getSize(); ++i) {
            treeToReturn->insert(arr[i]);
        }

        return PtrWrapper<bTreeForDict<TKey, TElement>>(treeToReturn);
    }

    PtrWrapper<bTreeForDict<TKey, TElement>> operator()(TElement* arr, size_t size, unsigned int t, std::function<int(const TKey&, const TKey&)> compare = TypeFunctor<TKey>{}) {        
        auto treeToReturn = new bTreeForDict<TKey, TElement>(t, compare);
        for (int i = 0; i < size; ++i) {
            treeToReturn->insert(arr[i]);
        }

        return PtrWrapper<bTreeBuilderForDict<TKey, TElement>>(treeToReturn);
    }
};*/


#endif