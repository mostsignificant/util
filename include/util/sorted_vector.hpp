/*
 * util - a collection of utility classes and functions for C++
 * <https://github.com/sourcechris/util>
 *
 * MIT License
 *
 * Copyright (c) 2020 Christian Göhring
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

#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace util {

template <class T, class Compare = std::less<T>,
          class Allocator = std::allocator<T>>
class sorted_vector {
public:
    using value_type      = T;
    using allocator_type  = Allocator;
    using size_type       = typename std::vector<T, Allocator>::size_type;
    using difference_type = typename std::vector<T, Allocator>::difference_type;
    using reference       = typename std::vector<T, Allocator>::reference;
    using const_reference = typename std::vector<T, Allocator>::const_reference;
    using pointer         = typename std::vector<T, Allocator>::pointer;
    using const_pointer   = typename std::vector<T, Allocator>::const_pointer;
    using iterator        = typename std::vector<T, Allocator>::iterator;
    using const_iterator  = typename std::vector<T, Allocator>::const_iterator;
    using reverse_iterator =
        typename std::vector<T, Allocator>::reverse_iterator;
    using const_reverse_iterator =
        typename std::vector<T, Allocator>::const_reverse_iterator;

    // ctor and dtor

    sorted_vector() noexcept;
    explicit sorted_vector(const Allocator& alloc) noexcept;
    sorted_vector(size_type count, const T& value,
                  const Allocator& alloc = Allocator());
    explicit sorted_vector(size_type        count,
                           const Allocator& alloc = Allocator());
    template <class InputIt>
    sorted_vector(InputIt first, InputIt last,
                  const Allocator& alloc = Allocator());
    sorted_vector(const sorted_vector& other);
    sorted_vector(const sorted_vector& other, const Allocator& alloc);
    sorted_vector(sorted_vector&& other) noexcept;
    sorted_vector(sorted_vector&& other, const Allocator& alloc);
    sorted_vector(std::initializer_list<T> ilist,
                  const Allocator&         alloc = Allocator());

    // element access

    reference       at(size_type pos);
    const_reference at(size_type pos) const;
    reference       operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference       front();
    const_reference front() const;
    reference       back();
    const_reference back() const;
    T*              data() noexcept;
    const T*        data() const noexcept;

    // iterators

    iterator               begin() noexcept;
    const_iterator         begin() const noexcept;
    const_iterator         cbegin() const noexcept;
    iterator               end() noexcept;
    const_iterator         end() const noexcept;
    const_iterator         cend() const noexcept;
    reverse_iterator       rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    reverse_iterator       rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;

    // capacity

    bool      empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    void      reserve(size_type new_cap);
    size_type capacity() const noexcept;
    void      shrink_to_fit();

    // modifiers

    void     clear() noexcept;
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
    void     pop_back();
    void     resize(size_type count);
    void     resize(size_type count, const value_type& value);
    void     swap(sorted_vector& other);

private:
    std::vector<T, Allocator> _elements;
};

}  // namespace util

template <class T, class Compare, class Allocator>
util::sorted_vector<T, Compare, Allocator>::sorted_vector() noexcept {}

template <class T, class Compare, class Allocator>
util::sorted_vector<T, Compare, Allocator>::sorted_vector(
    const Allocator& alloc) noexcept
    : _elements(alloc) {}

template <class T, class Compare, class Allocator>
util::sorted_vector<T, Compare, Allocator>::sorted_vector(
    size_type count, const T& value, const Allocator& alloc)
    : _elements(count, value, alloc) {}

template <class T, class Compare, class Allocator>
util::sorted_vector<T, Compare, Allocator>::sorted_vector(
    size_type count, const Allocator& alloc)
    : _elements(count, alloc) {}