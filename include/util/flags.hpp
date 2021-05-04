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

#ifndef THAT_THIS_UTIL_FLAGS_HEADER_HEADER_FILE_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_FLAGS_HEADER_HEADER_FILE_IS_ALREADY_INCLUDED

#ifndef UTIL_NOSTDLIB
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
 * This class is enabled to work with UTIL_NOSTDLIB defined.
 *
 * @tparam Enum the used enum
 * @tparam EnumUnderlyingType the enum's underlying type, 32-bit integer by default
 */
template <class Enum, class EnumUnderlyingType = util::int32>
class flags {
public:
    explicit flags(Enum value);
    flags(util::initializer_list<Enum> values);

    flags() = default;
    ~flags() = default;
    flags(flags&& other) noexcept = default;
    flags(const flags& other) = default;
    auto operator=(flags&& other) noexcept -> flags& = default;
    auto operator=(const flags& other) -> flags& = default;

    explicit operator EnumUnderlyingType() const;
    explicit operator bool() const noexcept;
    auto operator!() const noexcept -> bool;

    auto flip(Enum value) noexcept -> flags&;
    void reset() noexcept;
    void reset(Enum value) noexcept;
    auto set(Enum value, bool on = true) noexcept -> flags&;
    auto test(Enum value) const noexcept -> bool;

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
util::flags<Enum, EnumUnderlyingType>::flags(util::initializer_list<Enum> values) {
    for (auto&& value : values) {
        value_ |= value;
    }
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
auto util::flags<Enum, EnumUnderlyingType>::flip(Enum value) noexcept
    -> util::flags<Enum, EnumUnderlyingType>& {
    set(value, !test(value));
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
auto util::flags<Enum, EnumUnderlyingType>::set(Enum value, bool on) noexcept
    -> util::flags<Enum, EnumUnderlyingType>& {
    if (on) {
        value_ |= value;
    } else {
        value_ &= ~value;
    }
}

/**
 * Returns true if the given enum flag value is set or not.
 *
 * @snippet test/flags.test.cpp flags_test
 */
template <class Enum, class EnumUnderlyingType>
auto util::flags<Enum, EnumUnderlyingType>::test(Enum value) const noexcept -> bool {
    return value_ & value;
}

#endif  // THAT_THIS_UTIL_FLAGS_HEADER_HEADER_FILE_IS_ALREADY_INCLUDED