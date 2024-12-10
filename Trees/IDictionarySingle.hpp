#ifndef _TREES_DICT_SINGLE_HPP_
#define _TREES_DICT_SINGLE_HPP_

#include <stdexcept>
#include <concepts>

//#include "bTree.hpp"
#include "bTreeForDict.hpp"
#include "TypeFunctor.hpp"

const unsigned minimumDegree = 30;

template <typename TKey, typename TElement>
class IDictionary {
private:
    bTreeForDict<TKey, TElement> tree;

public:
    IDictionary(unsigned minDegree = minimumDegree, std::function<int(const TKey&, const TKey&)> compare = TypeFunctor<TKey>{}) : tree(minDegree, compare) {}

    int GetCount() const {
        return tree.GetSize();
    }

    TElement& Get(TKey key) {
        return tree.searchKey(key);
    }

    TElement& operator[](TKey key) {
        return tree.searchKey(key);
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