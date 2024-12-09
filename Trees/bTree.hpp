#ifndef _TREES_BTREES_HPP_
#define _TREES_BTREES_HPP_

#include "../Utility/SimplePair.hpp"
#include <iostream>
#include <exception>

enum class flags : char {
    NOT_MODIFIED,
    MODIFIED_NOT_ROOT,
    NEW_ROOT
};


template <typename T>
struct BNode {
    BNode<T>** child;
    T* key;
    unsigned int size;
    bool leaf;
};


template <typename T>
class BTree {
private:
    BNode<T>* root;
    bool (*lessThan)(const T&, const T&);
    unsigned minDegree;

public:
    BTree(unsigned, bool (*)(const T &, const T &));

    ~BTree();

    void insert(T);

    T remove(T);

    SimplePair<BNode<T>*, unsigned> search(T);

    T searchKey(T);

    void traverse() {
        traverse_util(root);
    }

    void traverse_util(BNode<T>* x) {
        int i;
        for (i = 0; i < x->size; ++i) {
            if (!x->leaf) {
                traverse_util(x->child[i]);
            }
            std::cout << " " << x->key[i];
        }

        if (!x->leaf) {
            traverse_util(x->child[i]);
        }
    }

private:
    void initializeNode(BNode<T>*);

    void freeNode(BNode<T>*);

    unsigned findIndex(BNode<T>*, T);

    unsigned nodeInsert(BNode<T>*, T);

    T nodeDelete(BNode<T>*, unsigned);

    void splitChild(BNode<T>*, int);

    flags mergeChildren(BNode<T>*, unsigned);

    flags fixChildSize(BNode<T>*, unsigned);
};


template <typename T>
BTree<T>::BTree(unsigned t, bool (*compare)(const T &, const T &)) {
    minDegree = t;
    lessThan = compare;
    root = new BNode<T>();
    initializeNode(root);
    root->leaf = true;
}

template <typename T>
BTree<T>::~BTree<T>() {
    freeNode(root);
}

template <typename T>
void BTree<T>::insert(T k) {
    if (root->size == 2 * minDegree - 1) {
        BNode<T> *newRoot = new BNode<T>;
        initializeNode(newRoot);
        newRoot->leaf = false;
        newRoot->child[0] = root;
        root = newRoot;
        splitChild(newRoot, 0);
    }

    BNode<T>* curr = root;
    while (!curr->leaf)
    {
        int index = curr->size - 1;
        while (index >= 0 && lessThan(k, curr->key[index])) {
            index--;
        }
        index++;

        if (curr->child[index]->size == 2 * minDegree - 1) {
            splitChild(curr, index);
            if (lessThan(curr->key[index], k)) {
                index++;
            }
        }
        curr = curr->child[index];
    }

    nodeInsert(curr, k);
    
}


template <typename T>
T BTree<T>::remove(T k) {
    BNode<T>* curr = root;
    while(true) {
        unsigned i = findIndex(curr, k);

        if (i < curr->size && !(lessThan(curr->key[i], k) || lessThan(k, curr->key[i]))) {
            T toReturn = curr->key[i];

            if (curr->leaf) {
                nodeDelete(curr, i);
            }
            else {
                BNode<T>* leftKid = curr->child[i];
                BNode<T>* rightKid = curr->child[i + 1];

                if (leftKid->size >= minDegree) {
                    while(!(leftKid->leaf)) {
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

            flags result = fixChildSize(curr, i);
            if (result == flags::NEW_ROOT) {
                curr = root;
            }
            else {
                curr = curr->child[findIndex(curr, k)];
            }

        }
    }
}

template <typename T>
SimplePair<BNode<T>*, unsigned> BTree<T>::search(T k) {
    BNode<T>* x = root;

    while(true) {
        unsigned i = findIndex(x, k);

        if (i < x->size && !(lessThan(k, x->key[i]) || lessThan(x->key[i], k))) {
            return SimplePair<BNode<T>*, unsigned>(x, i);
        }

        else if (x->leaf) {
            return SimplePair<BNode<T>*, unsigned>(nullptr, 0);
        }

        else {
            x = x->child[i];
        }
    }
}

template <typename T>
T BTree<T>::searchKey(T k) {
    SimplePair<BNode<T>*, unsigned> node = search(k);
    if (node.first == nullptr) {
        throw std::invalid_argument ("SearchKey: invalid key");
    }
    return node.first->key[node.second];
}



template <typename T>
void BTree<T>::initializeNode(BNode<T>* x) {
    x->size = 0;
    x->key = new T[2 * minDegree - 1]();
    x->child = new BNode<T>*[2 * minDegree]();
}

template <typename T>
void BTree<T>::freeNode(BNode<T>* x) {
    if (!x->leaf) {
        for (unsigned i = 0; i <= x->size; ++i) {
            freeNode(x->child[i]);
        }
    }
    delete[] x->child;
    delete[] x->key;
    delete x;
}

template <typename T>
unsigned BTree<T>::findIndex(BNode<T>* x, T k) {
    unsigned i = 0;
    while (i < x->size && lessThan(x->key[i], k)) {
        ++i;
    }
    return i;
}

template <typename T>
unsigned BTree<T>::nodeInsert(BNode<T>* x, T k) {
    int index;

    for (index = x->size; index > 0 && lessThan(k, x->key[index - 1]); --index) {
        x->key[index] = x->key[index - 1];
        x->child[index + 1] = x->child[index];
    }

    x->child[index + 1] = x->child[index];
    x->key[index] = k;
    x->size++;

    return index;
}

template <typename T>
T BTree<T>::nodeDelete(BNode<T>* x, unsigned index) {
    T toReturn = x->key[index];

    x->size--;

    while(index < x->size) {
        x->key[index] = x->key[index + 1];
        x->child[index + 1] = x->child[index + 2];
        ++index;
    }

    return toReturn;
}

template <typename T>
void BTree<T>::splitChild(BNode<T>* x, int i) {
    BNode<T>* toSplit = x->child[i];
    BNode<T>* newNode = new BNode<T>();
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

template <typename T>
flags BTree<T>::mergeChildren(BNode<T>* parent, unsigned i) {
    BNode<T>* leftKid = parent->child[i];
    BNode<T>* rightKid = parent->child[i+1];

    leftKid->key[leftKid->size] = nodeDelete(parent, i);
    unsigned j = ++(leftKid->size);

    for (unsigned k = 0; k < rightKid->size; ++k) {
        leftKid->key[j + k] = rightKid->key[k];
        leftKid->child[j + k] = rightKid->child[k];
    }
    leftKid->size += rightKid->size;
    leftKid->child[leftKid->size] = rightKid->child[rightKid->size];

    delete[] rightKid->child;
    delete[] rightKid->key;
    delete rightKid;

    if (parent->size == 0) {
        root = leftKid;
        delete[] parent->child;
        delete[] parent->key;
        delete parent;
        return flags::NEW_ROOT;
    }

    return flags::MODIFIED_NOT_ROOT;
}

template <typename T>
flags BTree<T>::fixChildSize(BNode<T>* parent, unsigned index) {
    BNode<T>* kid = parent->child[index];

    if (kid->size < minDegree) {
        if (index != 0 && parent->child[index - 1]->size >= minDegree) {
            BNode<T>* leftKid = parent->child[index - 1];

            for (unsigned i = nodeInsert(kid, parent->key[index - 1]); i != 0; --i) {
                kid->child[i] = kid->child[i - 1];
            }
            kid->child[0] = leftKid->child[leftKid->size];
            parent->key[index - 1] = nodeDelete(leftKid, leftKid->size - 1);
        }

        else if (index != parent->size && parent->child[index + 1]->size >= minDegree) {
            BNode<T>* rightKid = parent->child[index + 1];
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
        return flags::MODIFIED_NOT_ROOT;
    }

    return flags::NOT_MODIFIED;
}

#endif