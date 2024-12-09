#ifndef _UTILITY_SIMPLE_PAIR_HPP_
#define _UTILITY_SIMPLE_PAIR_HPP_

#include <concepts>
#include "../FirstLabUtility/Move.h"

template <typename T1, typename T2, typename Other1, typename Other2>
    concept ConvertibleToPair = std::convertible_to<Other1, T1> && std::convertible_to<Other2, T2>;

template <typename T1, typename T2>
class SimplePair {
public:
    //typedef T1 first_type;
    //typedef T2 second_type;
    constexpr SimplePair() : first(), second() {}

    SimplePair(const SimplePair&) = default;

    SimplePair(SimplePair&&) = default;

    constexpr SimplePair(const T1& Val1, const T2& Val2) : first(Val1), second(Val2) {}

    template<typename Other1, typename Other2>
    requires ConvertibleToPair<T1, T2, Other1, Other2>
    constexpr SimplePair(const SimplePair<Other1, Other2>& Right)
        : first(Right.first), second(Right.second) {}

    template<typename Other1, typename Other2>
    requires ConvertibleToPair<T1, T2, Other1, Other2>
    constexpr SimplePair(const SimplePair<Other1, Other2>&& Right)
        : first(Move(Right.first)), second(Move(Right.second)) {}

    template<typename Other1, typename Other2>
    requires ConvertibleToPair<T1, T2, Other1, Other2>
    constexpr SimplePair(Other1 && Val1, Other2 && Val2)
        : first(Forward<Other1>(Val1)), second(Forward<Other2>(Val2)) {}

    SimplePair& operator=(const SimplePair& p) {
        if (this != &p) {
            first = p.first;
            second = p.second;
        }

        return *this;
    }

    template <typename U1, typename U2>
    requires ConvertibleToPair<T1, T2, U1, U2>
    SimplePair& operator=(const SimplePair<U1, U2>& p) {
        if (this != &p) {
            first = p.first;
            second = p.second;
        }

        return *this;
    }
    SimplePair& operator=(SimplePair && p) noexcept {
        if (this != &p) {
            first = Move(p.first);
            second = Move(p.second);
        }
        return *this;
    }
    template <typename U1, typename U2>
    requires ConvertibleToPair<T1, T2, U1, U2>
    SimplePair& operator=(SimplePair<U1, U2>&& p) {
        if (this != &p) {
            first = Move(p.first);
            second = Move(p.second);
        } 
        return *this;
    }

    void Swap(SimplePair& p) noexcept {
        Swap(first, p.first);
        Swap(second, p.second);
    }

    const T1& GetKey() const {
        return first;
    }

    const T2& GetElem() const {
        return second;
    }


private:
    T1 first;
    T2 second;
};


template <class T1, class T2>
    SimplePair(T1, T2) -> SimplePair<T1, T2>;


#endif