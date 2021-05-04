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

#ifndef UTIL_NOSTDLIB
#include <algorithm>
#include <array>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <vector>
namespace util {
using std::allocator;
using std::array;
using std::back_inserter;
using std::copy;
using std::distance;
using std::initializer_list;
using std::numeric_limits;
using std::out_of_range;
using std::ptrdiff_t;
using std::size_t;
using std::vector;
}  // namespace util
#else
#include <util.hpp>
#endif  // UTIL_NOSTDLIB

namespace util {

namespace detail {
template <bool IsConst, class T, util::size_t N, class Allocator>
class buffer_iterator;
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

    using iterator = detail::buffer_iterator<false, T, N, Allocator>;
    using const_iterator = detail::buffer_iterator<true, T, N, Allocator>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

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
    auto stack_data() noexcept -> pointer;
    auto stack_data() const noexcept -> const_pointer;
    auto heap_data() noexcept -> pointer;
    auto heap_data() const noexcept -> const_pointer;

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
    util::size_t stack_pos = 0U;      // position of the next available slot on the stack
    util::array<T, N> stack = {T()};  // fixed-size container of stack elements
    util::vector<T, Allocator> heap;  // dynamically growing container of heap elements
};

namespace detail {

/**
 * An iterator class that holds a pointer to a buffer element.
 */
template <bool IsConst, class T, util::size_t N, class Allocator>
class buffer_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = util::ptrdiff_t;
    using value_type = T;
    using reference = typename std::conditional<IsConst, const value_type&, value_type&>::type;
    using pointer = typename std::conditional<IsConst, const value_type*, value_type*>::type;
    using buffer_type = util::buffer<T, N, Allocator>;
    using buffer_pointer =
        typename std::conditional<IsConst, const buffer_type*, buffer_type*>::type;
    using size_type = typename buffer_type::size_type;

    explicit buffer_iterator(size_type pos, const buffer_pointer& buffer_ptr) noexcept
        : pos(pos), buffer_ptr(buffer_ptr) {}

    auto operator*() const -> reference { return buffer_ptr->operator[](pos); }
    auto operator->() -> pointer { return buffer_ptr->operator[](pos); }

    /**
     * Prefix increment of this iterator.
     *
     * @return a reference to this iterator after incrementing
     */
    auto operator++() -> buffer_iterator& {
        pos++;
        return *this;
    }

    /**
     * Postfix increment of this iterator.
     *
     * @return a copy to this iterator before incrementing
     */
    auto operator++(int) -> buffer_iterator {
        buffer_iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    friend auto operator==(const buffer_iterator& lhs, const buffer_iterator& rhs) -> bool {
        return lhs.pos == rhs.pos && lhs.buffer_ptr == rhs.buffer_ptr;
    };
    friend auto operator!=(const buffer_iterator& lhs, const buffer_iterator& rhs) -> bool {
        return lhs.pos != rhs.pos || lhs.buffer_ptr != rhs.buffer_ptr;
    };

private:
    size_type pos = 0;
    buffer_pointer buffer_ptr;
};

// assert if a buffer_iterator is trivially copy constructible
static_assert(std::is_trivially_copy_constructible<buffer<int>::iterator>::value, "");

// assert if a buffer_const_iterator is trivially copy constructible
static_assert(std::is_trivially_copy_constructible<buffer<int>::const_iterator>::value, "");

}  // namespace detail

/**
 * Constructs a buffer object from an initializer list.
 *
 * @snippet test/buffer.test.cpp buffer_ctor_initializer_list
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
 * @param pos the requested element's position
 * @throw out_of_range if pos >= size()
 * @return a reference to the requested element
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
 * @param pos the requested element's position
 * @return a reference to the requested element
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
 * Returns the first element from the buffer. Undefined behaviour if the buffer is empty.
 *
 * @snippet test/buffer.test.cpp buffer_front
 * @return a reference to the first element in the buffer
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::front() -> reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const buffer<T, N, Allocator>*>(this)->front());
}

/**
 * @see auto buffer<T, N, Allocator>::front -> reference
 * @snippet test/buffer.test.cpp buffer_front_const
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::front() const -> const_reference {
    return stack[0];
}

/**
 * Returns the last element from the buffer. Undefined behaviour if the buffer is empty.
 *
 * @snippet test/buffer.test.cpp buffer_back
 * @return a reference to the last element in the buffer
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::back() -> reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const buffer<T, N, Allocator>*>(this)->back());
}

/**
 * @see auto buffer<T, N, Allocator>::back -> reference
 * @snippet test/buffer.test.cpp buffer_back_const
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::back() const -> const_reference {
    if (stack_pos == N) {
        return heap.back();
    }

    return stack[stack_pos - 1];
}

/**
 * Returns a direct pointer to the memory used internally by the buffer to store its stack elements.
 *
 * @snippet test/buffer.test.cpp buffer_stack_data
 * @return a pointer to the first stack element in the array used internally by the buffer
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::stack_data() noexcept -> pointer {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<pointer>(const_cast<const buffer<T, N, Allocator>*>(this)->stack_data());
}

/**
 * @see auto buffer<T, N, Allocator>::stack_data -> pointer
 * @snippet test/buffer.test.cpp buffer_stack_data_const
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::stack_data() const noexcept -> const_pointer {
    return stack.data();
}

/**
 * Returns a direct pointer to the memory used internally by the buffer to store its heap elements.
 *
 * @snippet test/buffer.test.cpp buffer_heap_data
 * @return a pointer to the first heap element in the array used internally by the buffer
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::heap_data() noexcept -> pointer {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<pointer>(const_cast<const buffer<T, N, Allocator>*>(this)->heap_data());
}

/**
 * @see auto buffer<T, N, Allocator>::heap_data -> pointer
 * @snippet test/buffer.test.cpp buffer_heap_data_const
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::heap_data() const noexcept -> const_pointer {
    return heap.data();
}

/**
 * Returns an iterator to the first element of the buffer. If the buffer is empty, the returned
 * iterator will be equal to end().
 *
 * @snippet an iterator to the first element
 * @return an iterator to the first element
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::begin() noexcept -> iterator {
    return iterator(0, this);
}

/**
 * @see auto buffer<T, N, Allocator>::begin -> iterator
 * @snippet test/buffer.test.cpp buffer_begin_const
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::begin() const noexcept -> const_iterator {
    return const_iterator(0, this);
}

/**
 * Returns a const_iterator to the first element of the buffer.
 *
 * @snippet test/buffer.test.cpp buffer_cbegin
 * @return a const_iterator to the first element
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::cbegin() const noexcept -> const_iterator {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) calls similar const-method
    return const_cast<const buffer*>(this)->begin();
}

/**
 * Returns an iterator to the element past the last element of the buffer.
 *
 * @snippet test/buffer.test.cpp buffer_end
 * @return an iterator to the position past the last element
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::end() noexcept -> iterator {
    return iterator(size(), this);
}

/**
 * @see auto buffer<T, N, Allocator>::end -> iterator
 * @snippet test/buffer.test.cpp buffer_end_const
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::end() const noexcept -> const_iterator {
    return const_iterator(size(), this);
}

/**
 * Returns a const_iterator to the element past the last element of the buffer.
 *
 * @snippet test/buffer.test.cpp buffer_cend
 * @return an iterator to the position past the last element
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::cend() const noexcept -> const_iterator {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) calls similar const-method
    return const_cast<const buffer*>(this)->end();
}

/**
 * Checks if the buffer has no elements.
 *
 * @snippet test/buffer.test.cpp buffer_empty
 * @return true if the buffer is empty, false otherwise
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::empty() const noexcept -> bool {
    return stack_pos == 0;
}

/**
 * Returns the current number of elements in the buffer (stack and heap).
 *
 * @snippet test/buffer.test.cpp buffer_size
 * @return the current number of elements in the buffer
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::size() const noexcept -> size_type {
    if (stack_pos < N) {
        return stack_pos;
    }
    return N + heap.size();
}

/**
 * Returns the maximum number of elements the container is able to hold.
 *
 * @snippet test/buffer.test.cpp buffer_size
 * @return the current number of elements in the buffer
 */
template <class T, util::size_t N, class Allocator>
auto buffer<T, N, Allocator>::max_size() const noexcept -> size_type {
    return stack.max_size() + heap.max_size();
}

}  // namespace util

#endif  // THAT_THIS_UTIL_BUFFER_HEADER_IS_ALREADY_INCLUDED