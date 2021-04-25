/*
 * util - a collection of utility classes and functions for C++
 * <https://github.com/mostsignificant/util>
 *
 * MIT License
 *
 * Copyright (c) 2018 Christian Göhring
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

#include <algorithm>
#include <array>
#include <memory>
#include <vector>

namespace util {

namespace detail {

template <class Type>
struct buffer_iterator;
template <class Type>
struct buffer_const_iterator;

}  // namespace detail

/** @brief A buffer class with a fixed-size base storage and dynamic memory for
 * additional storage.
 *
 * The buffer class is a container for values with a base fixed-size memory part
 * and additional dynamic part. This means that a number of values less than the
 * fixed-size parameter are stored on the stack and a number of values greater
 * than the fixed-size parameter are stored on the heap can can grow
 * dynamically.
 *
 * @tparam Type the type of values used in the buffer
 * @tparam Size the base part fixed size of the buffer
 * @tparam Allocator the allocator for the dynamic part of the buffer
 */
template <class Type, std::size_t Size = 24,
          class Allocator = std::allocator<Type>>
class buffer {
public:
    using allocator_type = Allocator;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;
    using value_type = Type;

    using iterator = detail::buffer_iterator<Type>;
    using const_iterator = detail::buffer_const_iterator<Type>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type* const;

    buffer(const std::initializer_list<Type>& list);

    bool empty() const noexcept;
    size_type size() const noexcept;

private:
    std::size_t stack_position = 0U;
    std::array<Type, Size> stack;
    std::vector<Type, Allocator> heap;
};

/** @brief Constructs a buffer object from an initializer list.
 *
 * @code{.cpp}
 *     const util::dat::buffer<int> numbers({1, 2, 3});
 *     assert(numbers.size() == 3);
 *     assert(numbers[0] == 1);
 * @endcode
 *
 * @param list A initializer list containing the initial elements for this
 * buffer
 */
template <class Type, std::size_t Size, class Allocator>
buffer<Type, Size, Allocator>::buffer(const std::initializer_list<Type>& list) {
    if (list.size() <= Size) {
        std::copy(list.begin(), list.end(), stack.begin());
        stack_position = list.size();
    } else {
        std::copy(list.begin(), list.begin() + Size, stack.begin());
        heap.reserve(std::distance(list.begin() + Size, list.end()));
        std::copy(list.begin() + Size, list.end(), std::back_inserter(heap));
        stack_position = Size;
    }
}

/** @brief Returns the current number of elements in the buffer.
 *
 * @code{.cpp}
 *     const util::buffer<float> floaters({ 1.0f, 1.1f, 1.2f });
 *     assert(floaters.size() == 3);
 * @endcode
 *
 * @return the current number of elements in the buffer
 */
template <class Type, std::size_t Size, class Allocator>
typename buffer<Type, Size, Allocator>::size_type
buffer<Type, Size, Allocator>::size() const noexcept {
    return stack_position + heap.size();
}

/** @brief Checks if the buffer has no elements.
 *
 * @code{.cpp}
 *     const util::buffer<double> doubles;
 *     assert(doubles.empty());
 *     doubles.push_back(1.0);
 *     assert(!doubles.empty());
 * @endcode
 *
 * @return true if the buffer is empty, false otherwise
 */
template <class Type, std::size_t Size, class Allocator>
bool buffer<Type, Size, Allocator>::empty() const noexcept {
    return stack_position == 0;
}

}  // namespace util