/*
 * util - a collection of utility classes and functions for C++
 * <https://github.com/mostsignificant/util>
 *
 * MIT License
 *
 * Copyright (c) 2020-2021 Christian Göhring
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef THAT_THIS_UTIL_ARRAY_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_ARRAY_HEADER_IS_ALREADY_INCLUDED

#ifndef UTIL_NO_STD_LIBRARY
#include <cstddef>
#include <iterator>
#include <stdexcept>
namespace util {
using std::out_of_range;
using std::ptrdiff_t;
using std::reverse_iterator;
using std::size_t;
}  // namespace util
#else
#include <util.hpp>
#endif  // UTIL_NO_STD_LIBRARY

namespace util {

/**
 * A container for continous fixed-size data.
 *
 * @snippet test/array.test.cpp array_ctor
 */
template <class T, util::size_t N>
struct array {
    using value_type = T;
    using size_type = util::size_t;
    using difference_type = util::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = pointer;
    using const_iterator = const_pointer;
    using reverse_iterator = util::reverse_iterator<iterator>;
    using const_reverse_iterator = util::reverse_iterator<const_iterator>;

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
    constexpr auto rbegin() noexcept -> iterator;
    constexpr auto rbegin() const noexcept -> const_iterator;
    constexpr auto crbegin() const noexcept -> const_iterator;
    constexpr auto rend() noexcept -> iterator;
    constexpr auto rend() const noexcept -> const_iterator;
    constexpr auto crend() const noexcept -> const_iterator;

    constexpr auto empty() const noexcept -> bool;
    constexpr auto size() const noexcept -> size_type;
    constexpr auto max_size() const noexcept -> size_type;

    constexpr void fill(const T& value);
    constexpr void swap(array& other);

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays,misc-non-private-member-variables-in-classes)
    T elements[N] = {T()};
};

/**
 * Extracts the Ith element element from the array.
 *
 * Contrary to array's at() behaviour, the parameter I is checked at compile-time to not be out of
 * range.
 *
 * @param a the array to get the Ith element from
 * @tparam I the position of the element to get
 * @tparam T the type of elements of the array
 * @tparam N the size of the array
 */
template <util::size_t I, class T, util::size_t N>
constexpr auto get(array<T, N>& a) noexcept -> T&;

/**
 * @see
 */
template <util::size_t I, class T, util::size_t N>
constexpr auto get(array<T, N>& a) noexcept -> T&&;

template <util::size_t I, class T, util::size_t N>
constexpr auto get(const array<T, N>& a) noexcept -> const T&;

template <util::size_t I, class T, util::size_t N>
constexpr auto get(const array<T, N>& a) noexcept -> const T&&;

template <class T, class... U>
array(T, U...) -> array<T, 1 + sizeof...(U)>;

/**
 * Returns the element at the given position with boundary checking.
 *
 * @snippet test/array.test.cpp array_at
 * @param pos the requested element's position
 * @throw out_of_range if pos >= size()
 * @return a reference to the requested element
 */
template <class T, util::size_t N>
constexpr auto array<T, N>::at(size_type pos) -> array<T, N>::reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const array<T, N>*>(this)->at(pos));
}

/**
 * @see auto array<T, N>::at(size_type pos) -> reference
 * @snippet test/array.test.cpp array_at_const
 */
template <class T, util::size_t N>
constexpr auto array<T, N>::at(size_type pos) const -> array<T, N>::const_reference {
    if (!(pos < size())) {
        throw util::out_of_range{"pos is out of range"};
    }

    return elements[pos];
}

/**
 * Returns the element at the given position without boundary checking.
 *
 * @snippet test/array.test.cpp array_operator_square_brackets
 * @param pos the requested element's position
 * @return a reference to the requested element
 */
template <class T, util::size_t N>
constexpr auto array<T, N>::operator[](size_type pos) -> array<T, N>::reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const array<T, N>*>(this)->operator[](pos));
}

/**
 * @see auto array<T, N>::operator(size_type pos) -> reference
 * @snippet test/array.test.cpp array_operator_square_brackets_const
 */
template <class T, util::size_t N>
constexpr auto array<T, N>::operator[](size_type pos) const -> array<T, N>::const_reference {
    return elements[pos];
}

/**
 * Returns a direct pointer to the memory used internally by the array.
 *
 * @snippet test/array.test.cpp array_data
 * @return a pointer to the first element in the array used internally by the array
 */
template <class T, util::size_t N>
constexpr auto array<T, N>::data() noexcept -> array<T, N>::pointer {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<pointer>(const_cast<const array<T, N>*>(this)->data());
}

/**
 * @see auto array<T, N>::data -> pointer
 * @snippet test/array.test.cpp array_const_data
 */
template <class T, util::size_t N>
constexpr auto array<T, N>::data() const noexcept -> array<T, N>::const_pointer {
    return &elements[0];
}

template <class T, util::size_t N>
constexpr auto array<T, N>::begin() noexcept -> iterator {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<pointer>(const_cast<const array<T, N>*>(this)->begin());
}

template <class T, util::size_t N>
constexpr auto array<T, N>::begin() const noexcept -> const_iterator {
    return elements[0];
}

template <class T, util::size_t N>
constexpr auto array<T, N>::cbegin() const noexcept -> const_iterator {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return const_cast<const array<T, N>*>(this)->begin();
}

template <class T, util::size_t N>
constexpr auto array<T, N>::end() noexcept -> iterator {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<pointer>(const_cast<const array<T, N>*>(this)->end());
}

template <class T, util::size_t N>
constexpr auto array<T, N>::end() const noexcept -> const_iterator {
    return elements[N];
}

template <class T, util::size_t N>
constexpr auto array<T, N>::cend() const noexcept -> const_iterator {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    return const_cast<const array<T, N>*>(this)->end();
}

template <class T, util::size_t N>
constexpr auto array<T, N>::rbegin() noexcept -> iterator {
    return reverse_iterator(begin());
}

template <class T, util::size_t N>
constexpr auto array<T, N>::rbegin() const noexcept -> const_iterator {
    return const_reverse_iterator(begin());
}

template <class T, util::size_t N>
constexpr auto array<T, N>::crbegin() const noexcept -> const_iterator {
    return const_reverse_iterator(begin());
}

template <class T, util::size_t N>
constexpr auto array<T, N>::rend() noexcept -> iterator {
    return reverse_iterator(end());
}

template <class T, util::size_t N>
constexpr auto array<T, N>::rend() const noexcept -> const_iterator {
    return const_reverse_iterator(end());
}

template <class T, util::size_t N>
constexpr auto array<T, N>::crend() const noexcept -> const_iterator {
    return const_reverse_iterator(end());
}

template <class T, util::size_t N>
constexpr auto array<T, N>::empty() const noexcept -> bool {
    return N == 0;
}

template <class T, util::size_t N>
constexpr auto array<T, N>::size() const noexcept -> array<T, N>::size_type {
    return N;
}

template <class T, util::size_t N>
constexpr auto array<T, N>::max_size() const noexcept -> array<T, N>::size_type {
    return N;
}

template <class T, util::size_t N>
constexpr void array<T, N>::fill(const T& value) {
    for (auto& element : elements) {
        element = value;
    }
}

template <class T, util::size_t N>
constexpr void array<T, N>::swap(array& other) {
    constexpr const auto tmp = *this;
    *this = other;
    other = tmp;
}

template <util::size_t I, class T, util::size_t N>
constexpr auto get(array<T, N>& a) noexcept -> T& {
    static_assert(I < N, "I is out of range");
    return a[I];
}

template <util::size_t I, class T, util::size_t N>
constexpr auto get(array<T, N>& a) noexcept -> T&& {
    static_assert(I < N, "I is out of range");
    return a[I];
}

template <util::size_t I, class T, util::size_t N>
constexpr auto get(const array<T, N>& a) noexcept -> const T& {
    static_assert(I < N, "I is out of range");
    return a[I];
}

template <util::size_t I, class T, util::size_t N>
constexpr auto get(const array<T, N>& a) noexcept -> const T&& {
    static_assert(I < N, "I is out of range");
    return a[I];
}

}  // namespace util

#endif  // THAT_THIS_UTIL_ARRAY_HEADER_IS_ALREADY_INCLUDED