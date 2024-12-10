//#include "Trees/bTree.hpp"
#include "Sort/Comparator.h"
#include "Trees/bTreeBuilder.hpp"
//#include "Trees/IDictionary.hpp"
#include "Trees/IDictionarySingle.hpp"
#include "Trees/bTreeForDict.hpp"
#include "Trees/TypeFunctor.hpp"

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
        //IDictionary<int, int> dict(4u, pairIntCompareFunc<int>);
        IDictionary<int, int> dict(15);
        std::cout << dict.GetCount() << std::endl;

        for (int i = 0; i < 10; ++i) {
            dict.Add(i, 10 + i);
        }
        std::cout << dict.GetCount() << std::endl;

        for (int i = 0; i < 10; ++i) {
            std::cout << dict.ContainsKey(i) << " ";
        }

        std::cout << dict.Get(3) << std::endl;

        try {
            std::cout << dict.Get(15) << std::endl;
        } catch(...) {
            std::cout << "ok" << std::endl;
        }

        std::cout << dict.ContainsKey(15) << std::endl;

        
    }

   /*
   {
    auto start = std::chrono::high_resolution_clock::now();
    bTreeForDict<int, int> tree(100);

    for (int i = 0; i < 100000; ++i) {
        tree.insert(SimplePair<int, int>(1000 - i, 100 * i));
    }

    
    //tree.traverse();
    auto end = std::chrono::high_resolution_clock::now();
    double time_taken = 
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << time_taken << " ms" << std::endl;
   }*/

    return 0;
}
