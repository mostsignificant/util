/*
 * util - a collection of utility classes and functions for C++
 * <https://github.com/mostsignificant/util>
 *
 * MIT License
 *
 * Copyright (c) 2020 - 2021 Christian Göhring
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

#ifndef UTIL_NO_STD_LIBRARY
#include <cstdint>
#include <initializer_list>
namespace util {
using int32 = int32_t;
using std::initializer_list;
}  // namespace util
#else
#include <util.hpp>
#endif

namespace util {

/**
 * A helper for storing an OR-combination of enum values.
 *
 * This class is enabled to work with UTIL_NO_STD_LIBRARY defined.
 *
 * @tparam Enum the used enum
 * @tparam EnumUnderlyingType the enum's underlying type, 32-bit integer by
 * default
 */
template <class Enum, class EnumUnderlyingType = util::int32>
class flags {
public:
    flags(Enum value);
    flags(util::initializer_list<Enum> values);

    flags() = default;
    ~flags() = default;
    flags(flags&& other) = default;
    flags(const flags& other) = default;
    flags& operator=(flags&& other) = default;
    flags& operator=(const flags& other) = default;

    operator EnumUnderlyingType() const;
    operator bool() const noexcept;
    bool operator!() const noexcept;

    flags& flip(Enum value) noexcept;
    void reset() noexcept;
    void reset(Enum value) noexcept;
    flags& set(Enum value, bool on = true) noexcept;
    bool test(Enum value) const noexcept;

private:
    EnumUnderlyingType value_ = static_cast<EnumUnderlyingType>(0);
};

}  // namespace util

/**
 * Constructs a flags object initialized with the given enum value.
 */
template <class Enum, class EnumUnderlyingType>
util::flags<Enum, EnumUnderlyingType>::flags(Enum value) : value_(value) {}

/**
 * Constructs a flags object initialized with the flags from the
 * initializer_list OR'd together.
 */
template <class Enum, class EnumUnderlyingType>
util::flags<Enum, EnumUnderlyingType>::flags(
    util::initializer_list<Enum> values) {
    for (auto&& value : values) value_ |= value;
}

/**
 * Casts to the underlying type of this enum.
 *
 * Can be used if the value needs to be supplied to library functions or else.
 *
 * @snippet test/flags.test.cpp flags_operator_enumunderlyingtype
 */
template <class Enum, class EnumUnderlyingType>
util::flags<Enum, EnumUnderlyingType>::operator EnumUnderlyingType() const {
    return value_;
}

/**
 * Returns true if the flag is set to a value or false if not.
 *
 * @snippet test/flags.test.cpp flags_operator_bool
 */
template <class Enum, class EnumUnderlyingType>
util::flags<Enum, EnumUnderlyingType>::operator bool() const noexcept {
    return value_ != 0;
}

/**
 * Returns true if the flag is not set to a value or false if it is.
 *
 * @snippet test/flags.test.cpp flags_operator_exclamationmark
 */
template <class Enum, class EnumUnderlyingType>
bool util::flags<Enum, EnumUnderlyingType>::operator!() const noexcept {
    return !static_cast<bool>(*this);
}

/**
 * Flips a given flag value.
 *
 * @snippet test/flags.test.cpp flags_flip
 */
template <class Enum, class EnumUnderlyingType>
util::flags<Enum, EnumUnderlyingType>&
util::flags<Enum, EnumUnderlyingType>::flip(Enum value) noexcept {
    set(value, !test(value));
}

/**
 * Returns true if the given enum flag value is set or not.
 *
 * @snippet test/flags.test.cpp flags_test
 */
template <class Enum, class EnumUnderlyingType>
bool util::flags<Enum, EnumUnderlyingType>::test(Enum value) const noexcept {
    return value_ & value;
}

/**
 * Resets all flag values.
 *
 * @snippet test/flags.test.cpp flags_reset_all
 */
template <class Enum, class EnumUnderlyingType>
void util::flags<Enum, EnumUnderlyingType>::reset() noexcept {
    value_ = static_cast<EnumUnderlyingType>(0);
}

/**
 * Resets the given flag value.
 *
 * @snippet test/flags.test.cpp flags_reset
 */
template <class Enum, class EnumUnderlyingType>
void util::flags<Enum, EnumUnderlyingType>::reset(Enum value) noexcept {
    set(value, false);
}

/**
 * Toggles or untoggles a given flag value.
 *
 * @snippet test/flags.test.cpp flags_set
 */
template <class Enum, class EnumUnderlyingType>
util::flags<Enum, EnumUnderlyingType>&
util::flags<Enum, EnumUnderlyingType>::set(Enum value, bool on) noexcept {
    if (on)
        value_ |= value;
    else
        value_ &= ~value;
}

#endif  // THAT_THIS_UTIL_FLAGS_HEADER_HEADER_FILE_IS_ALREADY_INCLUDED