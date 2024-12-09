#ifndef _COMPARATOR_H_
#define _COMPARATOR_H_

#include <string>

int intCompareFunc(const int& a, const int& b) {
    return (a < b) ? -1 : (a > b) ? 1 : 0;
}

int stringCompareFunc(const std::string& a, const std::string& b) {
    return (a < b) ? -1 : (a > b) ? 1 : 0;
}





#endif