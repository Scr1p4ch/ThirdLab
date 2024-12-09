#ifndef _MOVE_H_
#define _MOVE_H_

#include "RemoveRef.h"

template <typename T>
constexpr remove_ref_type<T>&& Move(T&& arg) {
    return static_cast<remove_ref_type<T>&&>(arg);
}

template <typename T>
constexpr T&& Forward(remove_ref_type<T>& arg) {
    return static_cast<T&&>(arg);
}

template <typename T>
constexpr T&& Forward(remove_ref_type<T>&& arg) {
    return static_cast<T&&>(arg);
}

#endif