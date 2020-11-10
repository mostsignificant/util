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

#ifndef THAT_THIS_UTIL_FLAGS_HEADER_HEADER_FILE_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_FLAGS_HEADER_HEADER_FILE_IS_ALREADY_INCLUDED

#include <cstdint>
#include <initializer_list>

namespace util {

/** A helper for storing an OR-combination of enum values.
 *
 * @tparam Enum the used enum
 * @tparam EnumUnderlyingType the enum's underlying type, 32-bit integer by default
 */
template <class Enum, class EnumUnderlyingType = int32_t>
class flags {
public:
    flags(Enum value);
    flags(std::initializer_list<Enum> values);

    flags() = default;
    flags(flags<Enum, EnumUnderlyingType>&& other) = default;
    flags(const flags<Enum, EnumUnderlyingType>& other) = default;
    ~flags() = default;

    operator EnumUnderlyingType() const;
    bool operator!() const;

private:
    EnumUnderlyingType value = static_cast<EnumUnderlyingType>(0);
};

}  // namespace util

template <class Enum, class EnumUnderlyingType>
util::flags<Enum, EnumUnderlyingType>::flags(Enum value) : value(value) {}

template <class Enum, class EnumUnderlyingType>
util::flags<Enum, EnumUnderlyingType>::operator EnumUnderlyingType() const {
    return value;
}

template <class Enum, class EnumUnderlyingType>
util::flags<Enum, EnumUnderlyingType>::flags(std::initializer_list<Enum> values) {
    for (auto value : values) {
        this->value |= value;
    }
}

template <class Enum, class EnumUnderlyingType>
bool util::flags<Enum, EnumUnderlyingType>::operator!() const {
    return (value == 0);
}

#endif  // THAT_THIS_UTIL_FLAGS_HEADER_HEADER_FILE_IS_ALREADY_INCLUDED