#ifndef _TREES_TYPEFUNCTOR_HPP_
#define _TREES_TYPEFUNCTOR_HPP_

#include <functional>

template <typename T>
struct TypeFunctor {
    int operator()(const T& a, const T& b) {
        return (a < b) ? -1 : (a > b) ? 1 : 0;
    }

    operator std::function<int(const T&, const T&)>() {
        return [this](const T& a, const T& b) {
            return (*this)(a, b);
        };
    }
};







#endif