// SPDX-FileCopyrightText: 2021 Christian Göhring <mostsig@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef THAT_THIS_UTIL_ARRAY_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_ARRAY_HEADER_IS_ALREADY_INCLUDED

#include <cstddef>
#include <iterator>
#include <stdexcept>

#ifdef UTIL_ASSERT
#include "assert.hpp"
#endif

namespace util {

/**
 * A container for continous fixed-size data.
 *
 * @snippet test/array.test.cpp array_ctor
 */
template <class T, std::size_t N>
class array {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    constexpr auto at(size_type pos) -> reference;
    constexpr auto at(size_type pos) const -> const_reference;
    constexpr auto operator[](size_type pos) -> reference;
    constexpr auto operator[](size_type pos) const -> const_reference;
    constexpr auto front() -> reference;
    constexpr auto front() const -> const_reference;
    constexpr auto back() -> reference;
    constexpr auto back() const -> const_reference;
    constexpr auto data() noexcept -> pointer;
    constexpr auto data() const noexcept -> const_pointer;

    constexpr auto begin() noexcept -> iterator;
    constexpr auto begin() const noexcept -> const_iterator;
    constexpr auto cbegin() const noexcept -> const_iterator;
    constexpr auto end() noexcept -> iterator;
    constexpr auto end() const noexcept -> const_iterator;
    constexpr auto cend() const noexcept -> const_iterator;
    constexpr auto rbegin() noexcept -> reverse_iterator;
    constexpr auto rbegin() const noexcept -> const_reverse_iterator;
    constexpr auto crbegin() const noexcept -> const_reverse_iterator;
    constexpr auto rend() noexcept -> reverse_iterator;
    constexpr auto rend() const noexcept -> const_reverse_iterator;
    constexpr auto crend() const noexcept -> const_reverse_iterator;

    constexpr auto empty() const noexcept -> bool;
    constexpr auto size() const noexcept -> size_type;
    constexpr auto max_size() const noexcept -> size_type;

    constexpr void fill(const T& value);
    void swap(array& other);

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays,misc-non-private-member-variables-in-classes)
    T elements[N];
};

template <std::size_t I, class T, std::size_t N>
constexpr auto get(array<T, N>& a) noexcept -> T&;

template <std::size_t I, class T, std::size_t N>
constexpr auto get(array<T, N>& a) noexcept -> T&&;

template <std::size_t I, class T, std::size_t N>
constexpr auto get(const array<T, N>& a) noexcept -> const T&;

template <std::size_t I, class T, std::size_t N>
constexpr auto get(const array<T, N>& a) noexcept -> const T&&;

template <class T, class... U>
array(T, U...) -> array<T, 1 + sizeof...(U)>;

template <class T, size_t N>
constexpr auto operator==(const array<T, N>& lhs, const array<T, N>& rhs) -> bool;

template <class T, size_t N>
constexpr auto operator!=(const array<T, N>& lhs, const array<T, N>& rhs) -> bool;

template <class T, size_t N>
constexpr auto operator<(const array<T, N>& lhs, const array<T, N>& rhs) -> bool;

template <class T, size_t N>
constexpr auto operator<=(const array<T, N>& lhs, const array<T, N>& rhs) -> bool;

template <class T, size_t N>
constexpr auto operator>(const array<T, N>& lhs, const array<T, N>& rhs) -> bool;

template <class T, size_t N>
constexpr auto operator>=(const array<T, N>& lhs, const array<T, N>& rhs) -> bool;

/**
 * Returns the element at the given position with boundary checking.
 *
 * @snippet test/array.test.cpp array_at
 * @param pos the requested element's position
 * @throw out_of_range if pos >= size()
 * @return a reference to the requested element
 */
template <class T, std::size_t N>
constexpr auto array<T, N>::at(size_type pos) -> array<T, N>::reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const array<T, N>*>(this)->at(pos));
}

/**
 * @see auto array<T, N>::at(size_type pos) -> reference
 * @snippet test/array.test.cpp array_at_const
 */
template <class T, std::size_t N>
constexpr auto array<T, N>::at(size_type pos) const -> array<T, N>::const_reference {
    if (!(pos < size())) {
        throw std::out_of_range{"pos is out of range"};
    }

    return elements[pos];
}

/**
 * Returns the element at the given position without boundary checking.
 *
 * @snippet test/array.test.cpp array_operator_square_brackets
 * @param pos the requested element's position
 * @throw util::assertion if pos >= size() and UTIL_ASSERT defined
 * @return a reference to the requested element
 */
template <class T, std::size_t N>
constexpr auto array<T, N>::operator[](size_type pos) -> array<T, N>::reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const array<T, N>*>(this)->operator[](pos));
}

/**
 * @see auto array<T, N>::operator(size_type pos) -> reference
 * @snippet test/array.test.cpp array_operator_square_brackets_const
 */
template <class T, std::size_t N>
constexpr auto array<T, N>::operator[](size_type pos) const -> array<T, N>::const_reference {
#ifdef UTIL_ASSERT
    util_assert(pos < size());
#endif
    return elements[pos];
}

/**
 * Returns the first element of the array.
 *
 * @snippet test/array.test.cpp array_front
 * @return the first element of the array
 */
template <class T, std::size_t N>
constexpr auto array<T, N>::front() -> reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const array<T, N>*>(this)->front());
}

/**
 * @see auto array<T, N>::front() -> reference
 * @snippet test/array.test.cpp array_front_const
 */
template <class T, std::size_t N>
constexpr auto array<T, N>::front() const -> const_reference {
    return elements[0];
}

/**
 * Returns the last element of the array.
 *
 * @snippet test/array.test.cpp array_back
 * @return the last element of the array
 */
template <class T, std::size_t N>
constexpr auto array<T, N>::back() -> reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const array<T, N>*>(this)->back());
}

/**
 * @see auto array<T, N>::back() -> reference
 * @snippet test/array.test.cpp array_back_const
 */
template <class T, std::size_t N>
constexpr auto array<T, N>::back() const -> const_reference {
    return elements[N - 1];
}

/**
 * Returns a direct pointer to the memory used internally by the array.
 *
 * @snippet test/array.test.cpp array_data
 * @return a pointer to the first element in the array used internally by the array
 */
template <class T, std::size_t N>
constexpr auto array<T, N>::data() noexcept -> array<T, N>::pointer {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<pointer>(const_cast<const array<T, N>*>(this)->data());
}

/**
 * @see auto array<T, N>::data -> pointer
 * @snippet test/array.test.cpp array_const_data
 */
template <class T, std::size_t N>
constexpr auto array<T, N>::data() const noexcept -> array<T, N>::const_pointer {
    return elements;
}

/**
 * Returns an iterator to the first element or the end() iterator if size() == 0.
 *
 * @snippet test/array.test.cpp array_begin
 * @return an iterator to the first element
 */
template <class T, std::size_t N>
constexpr auto array<T, N>::begin() noexcept -> iterator {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<pointer>(const_cast<const array<T, N>*>(this)->begin());
}

template <class T, std::size_t N>
constexpr auto array<T, N>::begin() const noexcept -> const_iterator {
    return elements;
}

template <class T, std::size_t N>
constexpr auto array<T, N>::cbegin() const noexcept -> const_iterator {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return const_cast<const array<T, N>*>(this)->begin();
}

template <class T, std::size_t N>
constexpr auto array<T, N>::end() noexcept -> iterator {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<pointer>(const_cast<const array<T, N>*>(this)->end());
}

template <class T, std::size_t N>
constexpr auto array<T, N>::end() const noexcept -> const_iterator {
    return elements + N;
}

template <class T, std::size_t N>
constexpr auto array<T, N>::cend() const noexcept -> const_iterator {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return const_cast<const array<T, N>*>(this)->end();
}

template <class T, std::size_t N>
constexpr auto array<T, N>::rbegin() noexcept -> reverse_iterator {
    return reverse_iterator(end());
}

template <class T, std::size_t N>
constexpr auto array<T, N>::rbegin() const noexcept -> const_reverse_iterator {
    return const_reverse_iterator(end());
}

template <class T, std::size_t N>
constexpr auto array<T, N>::crbegin() const noexcept -> const_reverse_iterator {
    return const_reverse_iterator(cend());
}

template <class T, std::size_t N>
constexpr auto array<T, N>::rend() noexcept -> reverse_iterator {
    return reverse_iterator(begin());
}

template <class T, std::size_t N>
constexpr auto array<T, N>::rend() const noexcept -> const_reverse_iterator {
    return const_reverse_iterator(begin());
}

template <class T, std::size_t N>
constexpr auto array<T, N>::crend() const noexcept -> const_reverse_iterator {
    return const_reverse_iterator(cbegin());
}

template <class T, std::size_t N>
constexpr auto array<T, N>::empty() const noexcept -> bool {
    return N == 0;
}

template <class T, std::size_t N>
constexpr auto array<T, N>::size() const noexcept -> array<T, N>::size_type {
    return N;
}

template <class T, std::size_t N>
constexpr auto array<T, N>::max_size() const noexcept -> array<T, N>::size_type {
    return N;
}

template <class T, std::size_t N>
constexpr void array<T, N>::fill(const T& value) {
    for (auto& element : elements) {
        element = value;
    }
}

template <class T, std::size_t N>
void array<T, N>::swap(array& other) {
    const auto tmp = *this;
    *this = other;
    other = tmp;
}

/**
 * Extracts the Ith element element from the array.
 *
 * Contrary to array's at() behaviour, the parameter I is checked at compile-time to not be out
 * of range.
 *
 * @param a the array to get the Ith element from
 * @tparam I the position of the element to get
 * @tparam T the type of elements of the array
 * @tparam N the size of the array
 */
template <std::size_t I, class T, std::size_t N>
constexpr auto get(array<T, N>& a) noexcept -> T& {
    static_assert(I < N, "I is out of range");
    return a[I];
}

template <std::size_t I, class T, std::size_t N>
constexpr auto get(array<T, N>& a) noexcept -> T&& {
    static_assert(I < N, "I is out of range");
    return a[I];
}

template <std::size_t I, class T, std::size_t N>
constexpr auto get(const array<T, N>& a) noexcept -> const T& {
    static_assert(I < N, "I is out of range");
    return a[I];
}

template <std::size_t I, class T, std::size_t N>
constexpr auto get(const array<T, N>& a) noexcept -> const T&& {
    static_assert(I < N, "I is out of range");
    return a[I];
}

template <class T, size_t N>
constexpr auto operator==(const array<T, N>& lhs, const array<T, N>& rhs) -> bool {
    return !(lhs != rhs);
}

template <class T, size_t N>
constexpr auto operator!=(const array<T, N>& lhs, const array<T, N>& rhs) -> bool {
    if constexpr (N == 0) {
        return false;
    } else {
        for (std::size_t i = 0; i < N; ++i) {
            if (!(lhs.elements[i] == rhs.elements[i])) {
                return true;
            }
        }
        return false;
    }
}

template <class T, size_t N>
constexpr auto operator<(const array<T, N>& lhs, const array<T, N>& rhs) -> bool {
    if constexpr (N == 0) {
        return false;
    } else {
        for (std::size_t i = 0; i < N; ++i) {
            if (lhs.elements[i] < rhs.elements[i]) {
                return true;
            }
            if (rhs.elements[i] < lhs.elements[i]) {
                return false;
            }
        }
        return false;
    }
}

template <class T, size_t N>
constexpr auto operator<=(const array<T, N>& lhs, const array<T, N>& rhs) -> bool {
    return !(rhs < lhs);
}

template <class T, size_t N>
constexpr auto operator>(const array<T, N>& lhs, const array<T, N>& rhs) -> bool {
    return !(lhs <= rhs);
}

template <class T, size_t N>
constexpr auto operator>=(const array<T, N>& lhs, const array<T, N>& rhs) -> bool {
    return !(lhs < rhs);
}

/**
 * Specialization for empty array.
 */
template <class T>
class array<T, 0> {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    constexpr auto at(size_type pos) -> reference {
        pos = pos;
        throw std::out_of_range{"cannot access element of empty array"};
    }

    constexpr auto at(size_type pos) const -> const_reference {
        pos = pos;
        throw std::out_of_range{"cannot access element of empty array"};
    }

    constexpr auto operator[](size_type pos) -> reference {
        pos = pos;
        throw std::out_of_range{"cannot access element of empty array"};
    }

    constexpr auto operator[](size_type pos) const -> const_reference {
        pos = pos;
        throw std::out_of_range{"cannot access element of empty array"};
    }

    constexpr auto front() -> reference {
        throw std::out_of_range{"cannot access element of empty array"};
    }

    constexpr auto front() const -> const_reference {
        throw std::out_of_range{"cannot access element of empty array"};
    }

    constexpr auto back() -> reference {
        throw std::out_of_range{"cannot access element of empty array"};
    }

    constexpr auto back() const -> const_reference {
        throw std::out_of_range{"cannot access element of empty array"};
    }

    constexpr auto data() noexcept -> pointer {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        return reinterpret_cast<value_type*>(this);
    }

    constexpr auto data() const noexcept -> const_pointer {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        return reinterpret_cast<const value_type*>(this);
    }

    constexpr auto begin() noexcept -> iterator {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        return reinterpret_cast<value_type*>(this);
    }

    constexpr auto begin() const noexcept -> const_iterator {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        return reinterpret_cast<const value_type*>(this);
    }

    constexpr auto cbegin() const noexcept -> const_iterator {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
        return reinterpret_cast<const value_type*>(this);
    }

    constexpr auto end() noexcept -> iterator { return begin(); }
    constexpr auto end() const noexcept -> const_iterator { return begin(); }
    constexpr auto cend() const noexcept -> const_iterator { return cbegin(); }

    constexpr auto rbegin() noexcept -> reverse_iterator { return reverse_iterator(begin()); }

    constexpr auto rbegin() const noexcept -> const_reverse_iterator {
        return const_reverse_iterator(begin());
    }
    constexpr auto crbegin() const noexcept -> const_reverse_iterator {
        return const_reverse_iterator(cbegin());
    }

    constexpr auto rend() noexcept -> reverse_iterator { return rbegin(); }
    constexpr auto rend() const noexcept -> const_reverse_iterator { return rbegin(); }
    constexpr auto crend() const noexcept -> const_reverse_iterator { return crbegin(); }

    constexpr auto empty() const noexcept -> bool { return true; }
    constexpr auto size() const noexcept -> size_type { return 0; }
    constexpr auto max_size() const noexcept -> size_type { return 0; }

    constexpr void fill(const T& value) {}
    constexpr void swap(array& other) {}
};

}  // namespace util

#endif  // THAT_THIS_UTIL_ARRAY_HEADER_IS_ALREADY_INCLUDED