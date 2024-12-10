
#ifndef _TREES_BTREES_DICT_HPP_
#define _TREES_BTREES_DICT_HPP_

#include <iostream>
#include <exception>
#include "../Utility/SimplePair.hpp"
#include "TypeFunctor.hpp"
#include <functional>
#include <stack>

enum class flagsToReturn : char {
    NOT_MODIFIED,
    MODIFIED_NOT_ROOT,
    NEW_ROOT
};


template <typename TKey, typename TElement>
class bTreeForDict {
private:
    template <typename U1 = TKey, typename U2 = TElement>
    struct BNode {
        DynamicArray<BNode<SimplePair<TKey, TElement>>*> child;
        DynamicArray<SimplePair<TKey, TElement>> key;
        unsigned int size = 0u;
        bool leaf = false;
    };

    BNode<SimplePair<TKey, TElement>>* root = nullptr;
    //int (*comparator)(const TKey&, const TKey&) = 0;
    std::function<int(const TKey&, const TKey&)> comparator = nullptr;
    unsigned minDegree = 0u;
    int sizeOfTree = 0;

public:
    bTreeForDict(unsigned, std::function<int(const TKey&, const TKey&)> = TypeFunctor<TKey>{});

    ~bTreeForDict();

    inline int GetSize() const {
        return sizeOfTree;
    }

    void insert(SimplePair<TKey, TElement>);

    TElement remove(TKey);

    SimplePair<typename bTreeForDict<TKey, TElement>::BNode<SimplePair<TKey, TElement>>*, unsigned> search(TKey);

    TElement searchKey(TKey);

    void traverse(BNode<SimplePair<TKey, TElement>>* x = nullptr) {
        unsigned int i;
        if (!x) {
            x = root;
        }
        for (i = 0u; i < x->size; ++i) {
            if (!x->leaf) {
                traverse(x->child[i]);
            }
            std::cout << " " << x->key[i];
        }

        if (!x->leaf) {
            traverse(x->child[i]);
        }
    }


    class Iterator {
    private:
        using Node = typename bTreeForDict<TKey, TElement>::BNode<SimplePair<TKey, TElement>>;
        const bTreeForDict* tree; // Указатель на дерево
        std::stack<std::pair<Node*, unsigned>> stack; // Стек для обхода

        void pushLeft(Node* node) {
            while (node) {
                stack.push({node, 0}); // Пушим текущую ноду с индексом 0
                if (node->leaf) break;
                node = node->child[0]; // Идем в самый левый дочерний элемент
            }
        }

    public:
        Iterator(const bTreeForDict* tree) : tree(tree) {
            if (tree->root) {
                pushLeft(tree->root);
            }
        }

        bool hasNext() const {
            return !stack.empty();
        }

        SimplePair<TKey, TElement> next() {
            if (!hasNext()) {
                throw std::out_of_range("Iterator has no more elements");
            }

            auto [node, index] = stack.top();
            stack.pop();

            SimplePair<TKey, TElement> result = node->key[index];

            if (index + 1 < node->size) {
                stack.push({node, index + 1}); // Сохраняем следующий ключ в текущей ноде
            }

            if (!node->leaf) {
                pushLeft(node->child[index + 1]); // Идем в следующий дочерний узел
            }

            return result;
        }
    };

    Iterator begin() const {
        return Iterator(this);
    }

private:
    void initializeNode(BNode<SimplePair<TKey, TElement>>*);

    void freeNode(BNode<SimplePair<TKey, TElement>>*);

    unsigned findIndex(BNode<SimplePair<TKey, TElement>>*, TKey);

    unsigned nodeInsert(BNode<SimplePair<TKey, TElement>>*, SimplePair<TKey, TElement>);

    SimplePair<TKey, TElement> nodeDelete(BNode<SimplePair<TKey, TElement>>*, unsigned);

    void splitChild(BNode<SimplePair<TKey, TElement>>*, int);

    flagsToReturn mergeChildren(BNode<SimplePair<TKey, TElement>>*, unsigned);

    flagsToReturn fixChildSize(BNode<SimplePair<TKey, TElement>>*, unsigned);
};


template<typename TKey, typename TElement>
bTreeForDict<TKey, TElement>::bTreeForDict(unsigned t, std::function<int(const TKey&, const TKey&)> compare) {
    minDegree = t;
    comparator = compare;
    root = new BNode<SimplePair<TKey, TElement>>;
    initializeNode(root);
    root->leaf = true;
}

template <typename TKey, typename TElement>
bTreeForDict<TKey, TElement>::~bTreeForDict() {
    freeNode(root);
}

template <typename TKey, typename TElement>
void bTreeForDict<TKey, TElement>::insert(SimplePair<TKey, TElement> k) {
    if (root->size == 2 * minDegree - 1) {
        BNode<SimplePair<TKey, TElement>> *newRoot = new BNode<SimplePair<TKey, TElement>>;
        initializeNode(newRoot);
        newRoot->leaf = false;
        newRoot->child[0] = root;
        root = newRoot;
        splitChild(newRoot, 0);
    }

    BNode<SimplePair<TKey, TElement>>* curr = root;

    while (!curr->leaf) {
        int index = curr->size - 1;
        while (index >= 0 && -1 == comparator(k.first, curr->key[index].first)) {
            --index;
        }

        ++index;

        if(curr->child[index]->size == 2 * minDegree - 1) {
            splitChild(curr, index);
            if (-1 == comparator(curr->key[index].first, k.first)) {
                ++index;
            }
        }

        curr = curr->child[index];
    }

    ++sizeOfTree;
    nodeInsert(curr, k);
}

template <typename TKey, typename TElement>
TElement bTreeForDict<TKey, TElement>::remove(TKey k) {
    BNode<SimplePair<TKey, TElement>>* curr = root;
    --sizeOfTree;

    while (true) {
        unsigned i = findIndex(curr, k);

        if (i < curr->size && !(-1 == comparator(curr->key[i].first, k) || -1 == comparator(k, curr->key[i].first))) {
            TElement toReturn = curr->key[i].first;

            if (curr->leaf) {
                nodeDelete(curr, i);
            }
            else {
                BNode<SimplePair<TKey, TElement>>* leftKid = curr->child[i];
                BNode<SimplePair<TKey, TElement>>* rightKid = curr->child[i + 1];

                if (leftKid->size >= minDegree) {
                    while (!(leftKid->leaf)) {
                        fixChildSize(leftKid, leftKid->size);
                        leftKid = leftKid->child[leftKid->size];
                    }
                    curr->key[i] = nodeDelete(leftKid, leftKid->size - 1);
                }

                else if (rightKid->size >= minDegree) {
                    while(!(rightKid->leaf)) {
                        fixChildSize(rightKid, 0);
                        rightKid = rightKid->child[0];
                    }
                    curr->key[i] = nodeDelete(rightKid, 0);
                }

                else {
                    mergeChildren(curr, i);
                    curr = leftKid;
                    continue;
                }
            }
            return toReturn;
        }

        else {
            if (curr->leaf) {
                throw std::invalid_argument("Remove: Invalid key");
            }

            flagsToReturn result = fixChildSize(curr, i);
            if (result == flagsToReturn::NEW_ROOT) {
                curr = root;
            }
            else {
                curr = curr->child[findIndex(curr, k)];
            }

        }
    }
}

template <typename TKey, typename TElement>
SimplePair<typename bTreeForDict<TKey, TElement>::BNode<SimplePair<TKey, TElement>>*, unsigned> bTreeForDict<TKey, TElement>::search(TKey k) {
    BNode<SimplePair<TKey, TElement>>* x = root;

    while(true) {
        unsigned i = findIndex(x, k);

        if (i < x->size && !(-1 == comparator(k, x->key[i].first) || -1 == comparator(x->key[i].first, k))) {
            return SimplePair<BNode<SimplePair<TKey, TElement>>*, unsigned>(x, i);
        }

        else if (x->leaf) {
            return SimplePair<BNode<SimplePair<TKey, TElement>>*, unsigned>(nullptr, 0);
        }

        else {
            x = x->child[i];
        }
    }
}

template <typename TKey, typename TElement>
TElement bTreeForDict<TKey, TElement>::searchKey(TKey k) {
    SimplePair<BNode<SimplePair<TKey, TElement>>*, unsigned> node = search(k);
    if (node.first == nullptr) {
        throw std::invalid_argument ("SearchKey: invalid key");
    }
    return node.first->key[node.second].second;
}

template <typename TKey, typename TElement>
void bTreeForDict<TKey, TElement>::initializeNode(BNode<SimplePair<TKey, TElement>>* x) {
    x->size = 0;
    x->key = DynamicArray<SimplePair<TKey, TElement>>(2 * minDegree - 1);
    x->child = DynamicArray<BNode<SimplePair<TKey, TElement>>*>(2 * minDegree);
}

template <typename TKey, typename TElement>
void bTreeForDict<TKey, TElement>::freeNode(BNode<SimplePair<TKey, TElement>>* x) {
    if (!x->leaf) {
        for (unsigned i = 0; i <= x->size; ++i) {
            freeNode(x->child[i]);
        }
    }
    delete x;
}

template <typename TKey, typename TElement>
unsigned bTreeForDict<TKey, TElement>::findIndex(BNode<SimplePair<TKey, TElement>>* x, TKey k) {
    unsigned i = 0;
    while (i < x->size && -1 == comparator(x->key[i].first, k)) {
        ++i;
    }
    return i;
}

template <typename TKey, typename TElement>
unsigned bTreeForDict<TKey, TElement>::nodeInsert(BNode<SimplePair<TKey, TElement>>* x, SimplePair<TKey, TElement> k) {
    int index;

    for (index = x->size; index > 0 && -1 == comparator(k.first, x->key[index - 1].first); --index) {
        x->key[index] = x->key[index - 1];
        x->child[index + 1] = x->child[index];
    }

    x->child[index + 1] = x->child[index];
    x->key[index] = k;
    x->size++;

    return index;
}

template <typename TKey, typename TElement>
SimplePair<TKey, TElement> bTreeForDict<TKey, TElement>::nodeDelete(BNode<SimplePair<TKey, TElement>>* x, unsigned index) {
    SimplePair<TKey, TElement> toReturn = x->key[index];

    x->size--;

    while(index < x->size) {
        x->key[index] = x->key[index + 1];
        x->child[index + 1] = x->child[index + 2];
        ++index;
    }

    return toReturn;
}

template <typename TKey, typename TElement>
void bTreeForDict<TKey, TElement>::splitChild(BNode<SimplePair<TKey, TElement>>* x, int i) {
    BNode<SimplePair<TKey, TElement>>* toSplit = x->child[i];
    BNode<SimplePair<TKey, TElement>>* newNode = new BNode<SimplePair<TKey, TElement>>;
    initializeNode(newNode);
    newNode->leaf = toSplit->leaf;
    newNode->size = minDegree - 1;

    for (unsigned j = 0; j < minDegree - 1; ++j) {
        newNode->key[j] = toSplit->key[j + minDegree];
    }

    if (!toSplit->leaf) {
        for (unsigned j = 0; j < minDegree; ++j) {
            newNode->child[j] = toSplit->child[j + minDegree];
        }
    }
    toSplit->size = minDegree - 1;

    nodeInsert(x, toSplit->key[minDegree - 1]);
    x->child[i + 1] = newNode;
}

template <typename TKey, typename TElement>
flagsToReturn bTreeForDict<TKey, TElement>::mergeChildren(BNode<SimplePair<TKey, TElement>>* parent, unsigned i) {
    BNode<SimplePair<TKey, TElement>>* leftKid = parent->child[i];
    BNode<SimplePair<TKey, TElement>>* rightKid = parent->child[i+1];

    leftKid->key[leftKid->size] = nodeDelete(parent, i);
    unsigned j = ++(leftKid->size);

    for (unsigned k = 0; k < rightKid->size; ++k) {
        leftKid->key[j + k] = rightKid->key[k];
        leftKid->child[j + k] = rightKid->child[k];
    }
    leftKid->size += rightKid->size;
    leftKid->child[leftKid->size] = rightKid->child[rightKid->size];

    delete rightKid;

    if (parent->size == 0) {
        root = leftKid;
        delete parent;
        return flagsToReturn::NEW_ROOT;
    }

    return flagsToReturn::MODIFIED_NOT_ROOT;
}


template <typename TKey, typename TElement>
flagsToReturn bTreeForDict<TKey, TElement>::fixChildSize(BNode<SimplePair<TKey, TElement>>* parent, unsigned index) {
    BNode<SimplePair<TKey, TElement>>* kid = parent->child[index];

    if (kid->size < minDegree) {
        if (index != 0 && parent->child[index - 1]->size >= minDegree) {
            BNode<SimplePair<TKey, TElement>>* leftKid = parent->child[index - 1];

            for (unsigned i = nodeInsert(kid, parent->key[index - 1]); i != 0; --i) {
                kid->child[i] = kid->child[i - 1];
            }
            kid->child[0] = leftKid->child[leftKid->size];
            parent->key[index - 1] = nodeDelete(leftKid, leftKid->size - 1);
        }

        else if (index != parent->size && parent->child[index + 1]->size >= minDegree) {
            BNode<SimplePair<TKey, TElement>>* rightKid = parent->child[index + 1];
            nodeInsert(kid, parent->key[index]);
            kid->child[kid->size] = rightKid->child[0];
            rightKid->child[0] = rightKid->child[1];
            parent->key[index] = nodeDelete(rightKid, 0);
        }

        else if (index != 0) {
            return mergeChildren(parent, index - 1);
        }
        else {
            return mergeChildren(parent, index);
        }
        return flagsToReturn::MODIFIED_NOT_ROOT;
    }

    return flagsToReturn::NOT_MODIFIED;
};




#endif