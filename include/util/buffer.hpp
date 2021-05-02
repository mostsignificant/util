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

#ifndef THAT_THIS_UTIL_BUFFER_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_BUFFER_HEADER_IS_ALREADY_INCLUDED

#ifndef UTIL_NO_STD_LIBRARY
#include <algorithm>
#include <array>
#include <iterator>
#include <stdexcept>
#include <vector>
namespace util {
using std::allocator;
using std::array;
using std::back_inserter;
using std::copy;
using std::distance;
using std::initializer_list;
using std::out_of_range;
using std::ptrdiff_t;
using std::size_t;
using std::vector;
}  // namespace util
#else
#include <util.hpp>
#endif  // UTIL_NO_STD_LIBRARY

namespace util {

namespace detail {
template <class T>
struct buffer_iterator;
template <class T>
struct buffer_const_iterator;
}  // namespace detail

/** @brief A buffer class with a fixed-size base storage and dynamic memory for additional storage.
 *
 * The buffer class is a container for values with a base fixed-size memory part and additional
 * dynamic part. This means that a number of values less than the fixed-size parameter are stored on
 * the stack and a number of values greater than the fixed-size parameter are stored on the heap can
 * can grow dynamically.
 *
 * @tparam T the type of values used in the buffer
 * @tparam N the base part fixed size of the buffer
 * @tparam Allocator the allocator for the dynamic part of the buffer
 */
template <class T, util::size_t N = 16, class Allocator = util::allocator<T>>
class buffer {
public:
    using allocator_type = Allocator;
    using difference_type = util::ptrdiff_t;
    using size_type = util::size_t;
    using value_type = T;

    using iterator = detail::buffer_iterator<T>;
    using const_iterator = detail::buffer_const_iterator<T>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type* const;

    buffer() = default;
    ~buffer() = default;
    buffer(const buffer&) = default;
    buffer(buffer&&) noexcept = default;
    auto operator=(const buffer&) -> buffer& = default;
    auto operator=(buffer&&) noexcept -> buffer& = default;

    buffer(const util::initializer_list<T>& list);

    auto at(size_type pos) -> reference;
    auto at(size_type pos) const -> const_reference;
    auto operator[](size_type pos) -> reference;
    auto operator[](size_type pos) const -> const_reference;
    auto front() -> reference;
    auto front() const -> const_reference;
    auto back() -> reference;
    auto back() const -> const_reference;
    auto data() noexcept -> pointer;
    auto data() const noexcept -> const_pointer;

    auto begin() noexcept -> iterator;
    auto begin() const noexcept -> const_iterator;
    auto cbegin() const noexcept -> const_iterator;
    auto end() noexcept -> iterator;
    auto end() const noexcept -> const_iterator;
    auto cend() const noexcept -> const_iterator;
    auto rbegin() noexcept -> iterator;
    auto rbegin() const noexcept -> const_iterator;
    auto crbegin() const noexcept -> const_iterator;
    auto rend() noexcept -> iterator;
    auto rend() const noexcept -> const_iterator;
    auto crend() const noexcept -> const_iterator;

    auto empty() const noexcept -> bool;
    auto size() const noexcept -> size_type;
    auto max_size() const noexcept -> size_type;

    void resize(size_type n, const value_type& val);
    auto capacity() const noexcept -> size_type;

private:
    util::size_t stack_pos = 0U;
    util::array<T, N> stack = {T()};
    util::vector<T, Allocator> heap;
};

/**
 * Constructs a buffer object from an initializer list.
 *
 * @snippet test/buffer.test.cpp buffer_ctor_initializer_list
 *
 * @param list A initializer list containing the initial elements for this buffer
 */
template <class T, util::size_t N, class Allocator>
buffer<T, N, Allocator>::buffer(const util::initializer_list<T>& list) {
    if (list.size() <= N) {
        util::copy(list.begin(), list.end(), stack.begin());
        stack_pos = list.size();
    } else {
        util::copy(list.begin(), list.begin() + N, stack.begin());
        heap.reserve(util::distance(list.begin() + N, list.end()));
        util::copy(list.begin() + N, list.end(), util::back_inserter(heap));
        stack_pos = N;
    }
}

/**
 * Returns the element at the given position with boundary checking.
 *
 * @snippet test/buffer.test.cpp buffer_at
 *
 * @param pos the requested element's position
 * @throw out_of_range if pos >= size()
 * @return a reference to the requeste element
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::at(size_type pos) -> reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const buffer<T, N, Allocator>*>(this)->at(pos));
}

/**
 * @see auto buffer<T, N, Allocator>::at(size_type pos) -> reference
 * @snippet test/buffer.test.cpp buffer_at_const
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::at(size_type pos) const -> const_reference {
    if (pos >= size()) {
        throw util::out_of_range{"pos is out of range"};
    }

    if (pos < N) {
        return stack.at(pos);
    }
    return heap.at(pos - N);
}

/**
 * Returns the element at the given position without boundary checking.
 *
 * @snippet test/buffer.test.cpp buffer_operator_square_brackets
 *
 * @param pos the requested element's position
 * @return a reference to the requeste element
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::operator[](size_type pos) -> reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const buffer<T, N, Allocator>*>(this)->operator[](pos));
}

/**
 * @see auto buffer<T, N, Allocator>::operator(size_type pos) -> reference
 * @snippet test/buffer.test.cpp buffer_operator_square_brackets_const
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::operator[](size_type pos) const -> const_reference {
    if (pos < N) {
        return stack[pos];
    }
    return heap[pos - N];
}

/**
 * Returns the current number of elements in the buffer (stack and heap).
 *
 * @snippet test/buffer.test.cpp buffer_size
 *
 * @return the current number of elements in the buffer
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::size() const noexcept -> buffer<T, N, Allocator>::size_type {
    if (stack_pos < N) {
        return stack_pos;
    }
    return N + heap.size();
}

/**
 * Checks if the buffer has no elements.
 *
 * @return true if the buffer is empty, false otherwise
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::empty() const noexcept -> bool {
    return stack_pos == 0;
}

}  // namespace util

#endif  // THAT_THIS_UTIL_BUFFER_HEADER_IS_ALREADY_INCLUDED