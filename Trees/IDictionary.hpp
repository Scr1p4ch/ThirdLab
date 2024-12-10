#ifndef _IDICTIONARY_HPP_
#define _IDICTIONARY_HPP_


#include "bTree.hpp"
#include <stdexcept>
#include <concepts>

template<class T>
concept default_initializable =
    std::constructible_from<T> &&
    requires { T{}; ::new T; };


const unsigned minimumDegree = 50;

template <typename TKey, typename TElement>
requires default_initializable<TElement>
class IDictionary {
private:
    using PairType = SimplePair<TKey, TElement>;
    BTree<PairType> tree;

public:
    IDictionary(unsigned minDegree, int (*cmp)(const PairType&, const PairType&)) : tree(minDegree, cmp) {}

    int GetCount() const {
        return tree.GetSize();
    }

    TElement Get(TKey key) {
        PairType a = tree.searchKey(PairType(key, TElement{}));
        return a.second;
    }

    bool ContainsKey(TKey key) {
        try {
            tree.searchKey(PairType(key, TElement{}));
            return true;
        } catch(...) {
            return false;
        }
    }

    void Add(TKey key, TElement element) {
        tree.insert(PairType(key, element));
    }

    void Remove(TKey key) {
        tree.remove(PairType(key, TElement{}));
    }

    BTree<PairType>& getTree() {
        return tree;
    }

};


#endif