#ifndef _COMPARATOR_H_
#define _COMPARATOR_H_

#include <string>
#include "../Utility/SimplePair.hpp"

int intCompareFunc(const int& a, const int& b) {
    return (a < b) ? -1 : (a > b) ? 1 : 0;
}

int stringCompareFunc(const std::string& a, const std::string& b) {
    return (a < b) ? -1 : (a > b) ? 1 : 0;
}

template <typename TKey>
int pairIntCompareFunc(const SimplePair<TKey, int>& a, const SimplePair<TKey, int>& b) {
    int s1 = a.GetKey();
    int s2 = b.GetKey();

    return intCompareFunc(s1, s2);
}





#endif