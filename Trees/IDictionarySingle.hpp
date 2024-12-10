#ifndef _TREES_DICT_SINGLE_HPP_
#define _TREES_DICT_SINGLE_HPP_

#include <stdexcept>
#include <concepts>

//#include "bTree.hpp"
#include "bTreeForDict.hpp"
#include "TypeFunctor.hpp"

const unsigned minimumDegree = 50;

template <typename TKey, typename TElement>
class IDictionary {
private:
    bTreeForDict<TKey, TElement> tree;

public:
    IDictionary(unsigned minDegree, std::function<int(const TKey&, const TKey&)> compare = TypeFunctor<TKey>{}) : tree(minDegree, compare) {}

    int GetCount() const {
        return tree.GetSize();
    }

    TElement Get(TKey key) {
        TKey a = tree.searchKey(key);
        return a;
    }

    bool ContainsKey(TKey key) {
        try {
            tree.searchKey(key);
            return true;
        } catch(...) {
            return false;
        }
    }

    void Add(TKey key, TElement element) {
        tree.insert(SimplePair<TKey, TElement>(key, element));
    }

    void Remove(TKey key) {
        tree.remove(key);
    }

    bTreeForDict<TKey, TElement>& getTree() {
        return tree;
    }

};


#endif