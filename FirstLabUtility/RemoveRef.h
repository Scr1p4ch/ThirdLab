#ifndef _REMOVE_REF_H
#define _REMOVE_REF_H

template <typename T>
struct RemoveRef {
    using type = T;
};

template <typename T>
struct RemoveRef<T&> {
    using type = T;
};

template <typename T>
struct RemoveRef<T&&> {
    using type = T;
};

template <typename T>
using remove_ref_type = typename RemoveRef<T>::type;


#endif