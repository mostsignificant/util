/*
 * util - a collection of utility classes and functions for C++
 * <https://github.com/sourcechris/util>
 *
 * MIT License
 *
 * Copyright (c) 2020 Christian Göhring
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef THAT_THIS_UTIL_SORTED_VECTOR_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_SORTED_VECTOR_HEADER_IS_ALREADY_INCLUDED

#include <functional>
#include <memory>
#include <vector>

namespace util {

/**
 * A vector of elements that are kept sorted.
 *
 * This container works as a normal `std::vector <https://en.cppreference.com/w/cpp/container/vector>`_ with the feature
 * that its elements stay sorted. The elements are sorted depending on a given comparison function or the default
 * std::less comparing function. There is no push_back function because this would interfere with the sorting. Instead
 * this container features only insert functions to add elements.
 *
 * @snippet test/sorted_vector.test.cpp sorted_vector_ctor_ilist
 *
 * @tparam T The type of elements in this container.
 * @tparam Compare A comparison function object which returns ​true if the first argument is less than (i.e. is
 * ordered before) the second. The type must meet the requirements of Compare.
 * @tparam Allocator An allocator that is used to acquire and release memory and to construct and destroy the elements
 * in this container. The type must meet the requirements of Allocator. The behavior is undefined if
 * Allocator::value_type is not the same as T.
 */
template <class T, class Compare = std::less<T>, class Allocator = std::allocator<T>>
class sorted_vector {
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = typename std::vector<T, Allocator>::size_type;
    using difference_type = typename std::vector<T, Allocator>::difference_type;
    using reference = typename std::vector<T, Allocator>::reference;
    using const_reference = typename std::vector<T, Allocator>::const_reference;
    using pointer = typename std::vector<T, Allocator>::pointer;
    using const_pointer = typename std::vector<T, Allocator>::const_pointer;
    using iterator = typename std::vector<T, Allocator>::iterator;
    using const_iterator = typename std::vector<T, Allocator>::const_iterator;
    using reverse_iterator = typename std::vector<T, Allocator>::reverse_iterator;
    using const_reverse_iterator = typename std::vector<T, Allocator>::const_reverse_iterator;

    sorted_vector() noexcept;
    explicit sorted_vector(const Allocator& alloc) noexcept;
    sorted_vector(size_type count, const T& value, const Allocator& alloc = Allocator());
    explicit sorted_vector(size_type count, const Allocator& alloc = Allocator());
    template <class InputIt>
    sorted_vector(InputIt begin, InputIt end, const Allocator& alloc = Allocator());
    sorted_vector(const sorted_vector& other);
    sorted_vector(const sorted_vector& other, const Allocator& alloc);
    sorted_vector(sorted_vector&& other) noexcept;
    sorted_vector(sorted_vector&& other, const Allocator& alloc);
    sorted_vector(std::initializer_list<T> ilist, const Allocator& alloc = Allocator());

    // element access

    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    T* data() noexcept;
    const T* data() const noexcept;

    // iterators

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // capacity

    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    void reserve(size_type new_cap);
    size_type capacity() const noexcept;
    void shrink_to_fit();

    // modifiers

    void clear() noexcept;
    iterator insert(const T& value);
    iterator insert(T&& value);
    iterator insert(size_type count, const T& value);
    iterator insert(std::initializer_list<T> ilist);
    template <class InputIt>
    void insert(InputIt first, InputIt last);
    template <class... Args>
    iterator emplace(Args&&... args);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    void pop_back();
    void resize(size_type count);
    void resize(size_type count, const value_type& value);
    void swap(sorted_vector& other);

private:
    Compare comp = Compare();
    std::vector<T, Allocator> _elements;
};

template <class InputIt, class Compare = std::less<typename std::iterator_traits<InputIt>::value_type>,
          class Alloc = std::allocator<typename std::iterator_traits<InputIt>::value_type>>
sorted_vector(InputIt, InputIt, Alloc = Alloc())
    ->sorted_vector<typename std::iterator_traits<InputIt>::value_type, Compare, Alloc>;

template <class T, class Compare, class Allocator>
sorted_vector<T, Compare, Allocator>::sorted_vector() noexcept {}

template <class T, class Compare, class Allocator>
sorted_vector<T, Compare, Allocator>::sorted_vector(const Allocator& alloc) noexcept : _elements(alloc) {}

template <class T, class Compare, class Allocator>
sorted_vector<T, Compare, Allocator>::sorted_vector(size_type count, const T& value, const Allocator& alloc)
    : _elements(count, value, alloc) {}

template <class T, class Compare, class Allocator>
sorted_vector<T, Compare, Allocator>::sorted_vector(size_type count, const Allocator& alloc)
    : _elements(count, alloc) {}

template <class T, class Compare, class Allocator>
template <class InputIt>
sorted_vector<T, Compare, Allocator>::sorted_vector(InputIt begin, InputIt end, const Allocator& alloc)
    : _elements(begin, end, alloc) {
    std::sort(_elements.begin(), _elements.end(), comp);
}

template <class T, class Compare, class Allocator>
sorted_vector<T, Compare, Allocator>::sorted_vector(std::initializer_list<T> ilist, const Allocator& alloc)
    : sorted_vector(std::begin(ilist), std::end(ilist), alloc) {}

template <class T, class Compare, class Allocator>
typename sorted_vector<T, Compare, Allocator>::reference sorted_vector<T, Compare, Allocator>::at(size_type pos) {
    return const_cast<typename sorted_vector<T, Compare, Allocator>::reference>(
        const_cast<const sorted_vector<T, Compare, Allocator>*>(this)->at(pos));
}

template <class T, class Compare, class Allocator>
typename sorted_vector<T, Compare, Allocator>::const_reference sorted_vector<T, Compare, Allocator>::at(
    size_type pos) const {
    return _elements.at(pos);
}

template <class T, class Compare, class Allocator>
typename sorted_vector<T, Compare, Allocator>::reference sorted_vector<T, Compare, Allocator>::operator[](
    size_type pos) {
    return const_cast<typename sorted_vector<T, Compare, Allocator>::reference>(
        const_cast<const sorted_vector<T, Compare, Allocator>*>(this)->operator[](pos));
}

template <class T, class Compare, class Allocator>
typename sorted_vector<T, Compare, Allocator>::const_reference sorted_vector<T, Compare, Allocator>::operator[](
    size_type pos) const {
    return _elements.operator[](pos);
}

template <class T, class Compare, class Allocator>
typename sorted_vector<T, Compare, Allocator>::reference sorted_vector<T, Compare, Allocator>::front() {
    return const_cast<typename sorted_vector<T, Compare, Allocator>::reference>(
        const_cast<const sorted_vector<T, Compare, Allocator>*>(this)->front());
}

template <class T, class Compare, class Allocator>
typename sorted_vector<T, Compare, Allocator>::const_reference sorted_vector<T, Compare, Allocator>::front() const {
    return _elements.front();
}

template <class T, class Compare, class Allocator>
typename sorted_vector<T, Compare, Allocator>::reference sorted_vector<T, Compare, Allocator>::back() {
    return const_cast<typename sorted_vector<T, Compare, Allocator>::reference>(
        const_cast<const sorted_vector<T, Compare, Allocator>*>(this)->back());
}

template <class T, class Compare, class Allocator>
typename sorted_vector<T, Compare, Allocator>::const_reference sorted_vector<T, Compare, Allocator>::back() const {
    return _elements.back();
}

template <class T, class Compare, class Allocator>
T* sorted_vector<T, Compare, Allocator>::data() noexcept {
    return const_cast<T*>(const_cast<const sorted_vector<T, Compare, Allocator>*>(this)->data());
}

template <class T, class Compare, class Allocator>
const T* sorted_vector<T, Compare, Allocator>::data() const noexcept {
    return _elements.data();
}

/**
 * Returns the count of elements in this sorted vector.
 *
 * @snippet test/sorted_vector.test.cpp sorted_vector_size
 */
template <class T, class Compare, class Allocator>
typename sorted_vector<T, Compare, Allocator>::size_type sorted_vector<T, Compare, Allocator>::size() const noexcept {
    return _elements.size();
}

/**
 * Returns the current available allocated space for elements of this sorted vector.
 *
 * @snippet test/sorted_vector.test.cpp sorted_vector_capacity
 */
template <class T, class Compare, class Allocator>
typename sorted_vector<T, Compare, Allocator>::size_type sorted_vector<T, Compare, Allocator>::capacity() const
    noexcept {
    return _elements.capacity();
}

/**
 * Clears all elements from this sorted vector.
 *
 * Invalidates any references, pointers, or iterators referring to contained elements. Any past-the-end iterators are
 * also invalidated, but leaves the capacity() of the vector unchanged.
 *
 * @snippet test/sorted_vector.test.cpp sorted_vector_clear
 */
template <class T, class Compare, class Allocator>
void sorted_vector<T, Compare, Allocator>::clear() noexcept {
    _elements.clear();
}

/**
 * Inserts an element into the sorted vector.
 *
 * In contrast to the normal std::vector insert method, this insert does not take an additional position parameter. The
 * position is determined by the sorting algorithm. The method invalidates any references, pointers, or iterators
 * referring to contained elements. Any past-the-end iterators are also invalidated.
 *
 * @snippet test/sorted_vector.test.cpp sorted_vector_insert
 */
template <class T, class Compare, class Allocator>
typename sorted_vector<T, Compare, Allocator>::iterator sorted_vector<T, Compare, Allocator>::insert(const T& value) {
    return _elements.insert(std::lower_bound(_elements.begin(), _elements.end()), value, comp);
}

/**
 * @see sorted_vector<T , Compare, Allocator>::insert(const T& value)
 */
template <class T, class Compare, class Allocator>
typename sorted_vector<T, Compare, Allocator>::iterator sorted_vector<T, Compare, Allocator>::insert(T&& value) {
    return _elements.insert(std::lower_bound(_elements.begin(), _elements.end(), std::move(value), comp),
                            std::move(value));
}

}  // namespace util

#endif  // THAT_THIS_UTIL_SORTED_VECTOR_HEADER_IS_ALREADY_INCLUDED