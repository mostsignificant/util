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

#ifndef THAT_THIS_UTIL_RING_BUFFER_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_RING_BUFFER_HEADER_IS_ALREADY_INCLUDED

#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <stdexcept>

namespace util {

namespace detail {
template <bool IsConst, class T, std::size_t N>
class ring_buffer_iterator;
}  // namespace detail

/**
 * A fixed-size ring buffer implementation.
 */
template <class T, std::size_t N>
class ring_buffer {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = detail::ring_buffer_iterator<false, T, N>;
    using const_iterator = detail::ring_buffer_iterator<true, T, N>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    ring_buffer() = default;
    ~ring_buffer() = default;
    ring_buffer(ring_buffer&&) noexcept = default;
    ring_buffer(const ring_buffer&) noexcept = default;
    auto operator=(ring_buffer&&) noexcept -> ring_buffer& = default;
    auto operator=(const ring_buffer&) noexcept -> ring_buffer& = default;

    constexpr ring_buffer(std::initializer_list<T> ilist);

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

    constexpr auto empty() const noexcept -> bool;
    constexpr auto size() const noexcept -> size_type;
    constexpr auto max_size() const noexcept -> size_type;

    constexpr void push_back(const T& value);
    constexpr void push_back(T&& value);

private:
    std::array<T, N> elements;
    std::size_t first = 0;  // points to the beginning of the elements
    std::size_t last = 0;   // points to the last of the elements

    void inc() noexcept;
    void dec() noexcept;
};

template <class T, std::size_t N>
constexpr ring_buffer<T, N>::ring_buffer(std::initializer_list<T> ilist) {
    if (ilist.size() > N) {
        std::copy_n(ilist.end() - N, N, elements.begin());
        last = N - 1;
    } else {
        std::copy_n(ilist.begin(), ilist.size(), elements.begin());
        last = ilist.size() - 1;
    }
}

template <class T, std::size_t N>
constexpr auto ring_buffer<T, N>::at(size_type pos) -> reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const ring_buffer<T, N>*>(this)->at(pos));
}

template <class T, std::size_t N>
constexpr auto ring_buffer<T, N>::at(size_type pos) const -> const_reference {
    if (pos >= size()) {
        throw std::out_of_range{"pos is out of range"};
    }

    return operator[](pos);
}

template <class T, std::size_t N>
constexpr auto ring_buffer<T, N>::operator[](size_type pos) -> reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const ring_buffer<T, N>*>(this)->operator[](pos));
}

template <class T, std::size_t N>
constexpr auto ring_buffer<T, N>::operator[](size_type pos) const -> const_reference {
#ifdef UTIL_ASSERT
    util_assert(pos < size());
#endif

    return elements[(first + pos) % N];
}

template <class T, std::size_t N>
constexpr auto ring_buffer<T, N>::front() -> reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const ring_buffer<T, N>*>(this)->front());
}

template <class T, std::size_t N>
constexpr auto ring_buffer<T, N>::front() const -> const_reference {
    return elements[first];
}

template <class T, std::size_t N>
constexpr auto ring_buffer<T, N>::back() -> reference {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<reference>(const_cast<const ring_buffer<T, N>*>(this)->back());
}

template <class T, std::size_t N>
constexpr auto ring_buffer<T, N>::back() const -> const_reference {
    return elements[last];
}

template <class T, std::size_t N>
constexpr auto ring_buffer<T, N>::data() noexcept -> pointer {
    return elements.data();
}

template <class T, std::size_t N>
constexpr auto ring_buffer<T, N>::data() const noexcept -> const_pointer {
    return elements.data();
}

template <class T, std::size_t N>
constexpr auto ring_buffer<T, N>::empty() const noexcept -> bool {
    return first == 0 && last == 0;
}

template <class T, std::size_t N>
constexpr auto ring_buffer<T, N>::size() const noexcept -> size_type {
    if (first == 0 && last < N - 1) {
        return last - first;
    }
    return N;
}

template <class T, std::size_t N>
constexpr auto ring_buffer<T, N>::max_size() const noexcept -> size_type {
    return elements.max_size();
}

template <class T, std::size_t N>
constexpr void ring_buffer<T, N>::push_back(const T& value) {
    inc();
    elements[last] = value;
}

template <class T, std::size_t N>
constexpr void ring_buffer<T, N>::push_back(T&& value) {
    inc();
    elements[last] = value;
}

/**
 * Shifts the internal position pointers by one position forward with wrap around.
 */
template <class T, std::size_t N>
void ring_buffer<T, N>::inc() noexcept {
    if (++first >= N) {
        first = 0;
    }

    if (++last >= N) {
        last = 0;
    }
}

/**
 * Shifts the internal position pointers by one position backwards with wrap around.
 */
template <class T, std::size_t N>
void ring_buffer<T, N>::dec() noexcept {
    if (first == 0) {
        first = N - 1;
    } else {
        first--;
    }

    if (last == 0) {
        last = N - 1;
    } else {
        last--;
    }
}

}  // namespace util

#endif  // THAT_THIS_UTIL_RING_BUFFER_HEADER_IS_ALREADY_INCLUDED