/*
 * util - a collection of utility classes and functions for C++
 * <https://github.com/mostsignificant/util>
 *
 * MIT License
 *
 * Copyright (c) 2020-2021 Christian Göhring
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef THAT_THIS_UTIL_SORTED_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_SORTED_HEADER_IS_ALREADY_INCLUDED

#ifdef UTIL_ASSERT
#include <util.hpp>
#endif

#include <algorithm>
#include <array>
#include <forward_list>
#include <functional>
#include <list>
#include <memory>
#include <vector>

namespace util {

/**
 * A container of elements that are kept sorted.
 *
 * @snippet test/sorted.test.cpp sorted_ctor_ilist
 * @tparam Container the type of container to keep sorted
 * @tparam Compare A comparison function object which returns ​true if the first argument is less
 * than (i.e. is ordered before) the second. The type must meet the requirements of Compare.
 */
template <class Container, class Compare = std::less<typename Container::value_type>>
class sorted {
public:
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using const_reference = const value_type&;
    using const_pointer = const value_type*;
    using const_iterator = typename Container::const_iterator;

    using is_forward_list =
        std::is_same<Container, std::forward_list<value_type, typename Container::allocator_type>>;
    using is_list =
        std::is_same<Container, std::list<value_type, typename Container::allocator_type>>;

    sorted() noexcept = default;
    ~sorted() = default;
    sorted(const sorted&) = default;
    sorted(sorted&&) noexcept = default;
    auto operator=(const sorted&) -> sorted& = default;
    auto operator=(sorted&&) noexcept -> sorted& = default;

    template <class OtherContainer>
    explicit sorted(const OtherContainer& container);
    template <class InputIt>
    sorted(InputIt begin, InputIt end);
    sorted(std::initializer_list<value_type> ilist);

    // element access

    auto at(size_type pos) const -> const_reference;
    auto operator[](size_type pos) const -> const_reference;
    auto front() const -> const_reference;
    auto back() const -> const_reference;
    auto data() const noexcept -> const_pointer;

    // iterators

    auto begin() const noexcept -> const_iterator;
    auto cbegin() const noexcept -> const_iterator;
    auto end() const noexcept -> const_iterator;
    auto cend() const noexcept -> const_iterator;

    // capacity and size

    auto empty() const noexcept -> bool;
    auto size() const noexcept -> size_type;
    auto max_size() const noexcept -> size_type;
    auto capacity() const noexcept -> size_type;
    void reserve(size_type new_cap);
    void shrink_to_fit();
    void resize(size_type count);
    void resize(size_type count, const_reference value);

    // modifiers

    void clear() noexcept;
    auto insert(const_reference value) -> const_iterator;
    auto insert(value_type&& value) -> const_iterator;
    auto insert(std::initializer_list<value_type> ilist) -> const_iterator;
    template <class InputIt>
    void insert(InputIt first, InputIt last);
    template <class... Args>
    auto emplace(Args&&... args) -> const_iterator;
    auto erase(const_iterator pos) -> const_iterator;
    auto erase(const_iterator first, const_iterator last) -> const_iterator;
    void pop_back();
    void pop_front();
    void swap(sorted& other);

private:
    Compare comp = Compare();
    Container container;
};

template <class T, class Allocator = std::allocator<T>>
using sorted_forward_list = sorted<std::forward_list<T, Allocator>>;
template <class T, class Allocator = std::allocator<T>>
using sorted_list = sorted<std::list<T, Allocator>>;
template <class T, class Allocator = std::allocator<T>>
using sorted_vector = sorted<std::vector<T, Allocator>>;

/**
 * Constructs a sorted container from a given container of elements.
 *
 * @snippet test/sorted.test.cpp sorted_ctor_container
 * @tparam OtherContainer the type of the container to insert, can be the same as the underlying
 * container of this sorted container
 * @param container the container of elements to insert, must have begin() and end() methods
 * returning input iterators
 */
template <class Container, class Compare>
template <class OtherContainer>
sorted<Container, Compare>::sorted(const OtherContainer& container)
    : sorted(container.begin(), container.end()) {}

/**
 * Constructs a sorted container from a given range of elements to insert.
 *
 * @snippet test/sorted.test.cpp sorted_ctor_iter
 * @tparam InputIt the type of the input iterator
 * @param begin the beginning iterator of the range of elements to insert
 * @param end the iterator of the element one position after the last element
 */
template <class Container, class Compare>
template <class InputIt>
sorted<Container, Compare>::sorted(InputIt begin, InputIt end) {
    if constexpr (is_forward_list::value) {
        container.assign(begin, end);
        container.sort(comp);
    } else {
        for (; begin != end; ++begin) {
            container.insert(std::lower_bound(container.begin(), container.end(), *begin, comp),
                             *begin);
        }
    }
}

/**
 * Constructs a sorted container from a given initializer list.
 *
 * @snippet test/sorted.test.cpp sorted_ctor_ilist
 * @param ilist the list of elements to initalize the sorted container with
 */
template <class Container, class Compare>
sorted<Container, Compare>::sorted(std::initializer_list<value_type> ilist)
    : sorted(std::begin(ilist), std::end(ilist)) {}

/**
 * Returns a const reference to an element at the requested position with boundary checking.
 *
 * @snippet test/sorted.test.cpp sorted_at
 * @param pos the position of the element to return
 * @throw out_of_range if pos >= size()
 * @return a const reference to the element at the requested position
 */
template <class Container, class Compare>
auto sorted<Container, Compare>::at(size_type pos) const -> const_reference {
    if (pos >= size()) {
        throw std::out_of_range{"pos is out of range"};
    }

    if constexpr (is_forward_list::value || is_list::value) {
        auto it = container.begin();
        while (pos--) {
            ++it;
        }
        return *it;
    } else {
        return container.at(pos);
    }
}

/**
 * Returns a const reference to an element at the requested position without boundary checking.
 * Undefined behaviour if accessing a position >= size().
 *
 * @snippet test/sorted.test.cpp sorted_operator_square_brackets
 * @param pos the position of the element to return
 * @return a const reference to the element at the requested position
 */
template <class Container, class Compare>
auto sorted<Container, Compare>::operator[](size_type pos) const -> const_reference {
#ifdef UTIL_ASSERT
    util_assert(pos < size());
#endif  // UTIL_ASSERT

    if constexpr (is_forward_list::value || is_list::value) {
        auto it = container.begin();
        while (pos--) {
            ++it;
        }
        return *it;
    } else {
        return container.operator[](pos);
    }
}

template <class Container, class Compare>
auto sorted<Container, Compare>::front() const -> const_reference {
    return container.front();
}

template <class Container, class Compare>
auto sorted<Container, Compare>::back() const -> const_reference {
    return container.back();
}

template <class Container, class Compare>
auto sorted<Container, Compare>::data() const noexcept -> const_pointer {
    return container.data();
}

/**
 * Returns the count of elements in this sorted container.
 *
 * @snippet test/sorted.test.cpp sorted_size
 * @return the number of contained elements
 */
template <class Container, class Compare>
auto sorted<Container, Compare>::size() const noexcept -> size_type {
    if constexpr (is_forward_list::value) {
        size_type size = 0;
        for (auto it = container.begin(), end = container.end(); it != end; ++it) {
            size++;
        }
        return size;
    } else {
        return container.size();
    }
}

/**
 * Returns the current available allocated space for elements of this sorted container.
 *
 * @snippet test/sorted.test.cpp sorted_capacity
 */
template <class Container, class Compare>
auto sorted<Container, Compare>::capacity() const noexcept -> size_type {
    if constexpr (is_forward_list::value || is_list::value) {
        return container.max_size();
    } else {
        return container.capacity();
    }
}

/**
 * Clears all elements from this sorted container.
 *
 * Invalidates any references, pointers, or iterators referring to contained elements. Any
 * past-the-end iterators are also invalidated, but leaves the capacity() of the container
 * unchanged.
 *
 * @snippet test/sorted.test.cpp sorted_clear
 */
template <class Container, class Compare>
void sorted<Container, Compare>::clear() noexcept {
    container.clear();
}

/**
 * Inserts an element into the sorted container.
 *
 * In contrast to the normal container's insert method, this insert does not take an additional
 * position parameter. The position is determined by the sorting algorithm. The method invalidates
 * any references, pointers, or iterators referring to contained elements. Any past-the-end
 * iterators are also invalidated.
 *
 * @snippet test/sorted.test.cpp sorted_insert
 * @param value the element to insert
 * @return a const iterator to the inserted element
 */
template <class Container, class Compare>
auto sorted<Container, Compare>::insert(const_reference value) -> const_iterator {
    if constexpr (is_forward_list::value) {
        container.push_back(value);
        container.sort(comp);
    } else {
        return const_iterator(
            container.insert(std::lower_bound(container.begin(), container.end()), value, comp));
    }
}

/**
 * @see sorted<Container, Compare>::insert(const_reference value) ->
 * const_iterator
 */
template <class Container, class Compare>
auto sorted<Container, Compare>::insert(value_type&& value) -> const_iterator {
    if constexpr (is_forward_list::value) {
        auto it = container.begin();
        if (comp(value, *it)) {
            container.push_front(std::move(value));
            return container.cbegin();
        }

        for (auto next = ++container.begin(), end = container.end(); next != end; ++next, ++it) {
            if (comp(value, *next)) {
                return const_iterator(container.insert_after(it, std::move(value)));
            }
        }

        return const_iterator(container.insert_after(it, std::move(value)));

    } else {
        return const_iterator(container.insert(
            std::lower_bound(container.begin(), container.end(), std::move(value), comp),
            std::move(value)));
    }
}

}  // namespace util

#endif  // THAT_THIS_UTIL_SORTED_HEADER_IS_ALREADY_INCLUDED