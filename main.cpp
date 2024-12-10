/*#include <iostream>
#include <string>

#include "Trees/bTree.hpp"
#include "Utility/Comparator.hpp"

void printString(std::string s) {
    std::cout << s;
}

int main() {
    BTree<std::string> tree(6, stringLessThan, printString);

    tree.insert("apple");
    tree.insert("banana");
    tree.insert("cherry");

    tree.insert("hi");
    tree.insert("Hu");
    tree.insert("ban");
    tree.print();

    tree.remove("apple");
    tree.insert("Hehehehe");
    tree.insert("HUHUHU");

    tree.print();

    try {
        tree.searchKey("banana");
        std::cout << "Found banana!" << std::endl;
        std::cout << tree.searchKey("banana") << std::endl;
    } catch (BTREE_EXCEPTION e) {
        std::cerr << "Key not found." << std::endl;
    }

    return 0;
}

*/

//#include "Trees/bTree.hpp"
#include "Sort/Comparator.h"
#include "Trees/bTreeBuilder.hpp"
#include "Trees/IDictionary.hpp"
#include "Trees/bTreeForDict.hpp"

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>



int main() {

    bTreeBuilder<int> builder;
    /*
    {
        ArraySequence<int> arr(100);
        for (int i = 0; i < 100; ++i) {
            arr.append(i);
        }
        auto ptr = builder(4, arr, intCompareFunc);

        ptr->traverse();

    }

    {
        int arr[100];

        for (int i = 0; i < 100; ++i) {
            arr[i] = i;
        }

        auto ptr = builder(4, arr, intCompareFunc, 100);

        ptr->traverse();
    }*/

   /*
    {
        IDictionary<int, int> dict(4u, pairIntCompareFunc<int>);
        std::cout << dict.GetCount() << std::endl;

        for (int i = 0; i < 10; ++i) {
            dict.Add(i, 10 + i);
        }
        dict.getTree().traverse();
        std::cout << dict.Get(1) << std::endl;
        dict.Remove(0);
        dict.getTree().traverse();
    }*/

   /*{
        //IDictionary<int, int> dict(4u, pairIntCompareFunc<int>);
        IDictionary<int, int> dict(4u, intCompareFunc);
        std::cout << dict.GetCount() << std::endl;

        for (int i = 0; i < 10; ++i) {
            dict.Add(i, 10 + i);
        }
        std::cout << dict.GetCount() << std::endl;

        for (int i = 0; i < 10; ++i) {
            std::cout << dict.ContainsKey(i) << " ";
        }

        
    }*/

   {
    bTreeForDict<std::string, ArraySequence<int>> tree(2, stringCompareFunc);

    ArraySequence<int> a(6);
    ArraySequence<int> b(6);
    ArraySequence<int> c(6);

    for (int i = 0; i < 6; ++i) {
        a.append(i + 1);
        b.append(2 * i + 1);
        c.append(3 * i + 1);
    }

    tree.insert(SimplePair<std::string, ArraySequence<int>>("cat", a));
    tree.insert(SimplePair<std::string, ArraySequence<int>>("dog", b));
    tree.insert(SimplePair<std::string, ArraySequence<int>>("who", c));

    
    tree.traverse();
   }

    return 0;
}
