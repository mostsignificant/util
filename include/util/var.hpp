// SPDX-FileCopyrightText: 2021 Christian Göhring <mostsig@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef THAT_THIS_UTIL_VAR_HEADER_HEADER_FILE_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_VAR_HEADER_HEADER_FILE_IS_ALREADY_INCLUDED

#include <utility>

namespace util {

/**
 * A wrapper for strongly typed variables.
 *
 * This class can be used to wrap a basic data type in C++ to get string typing through named types.
 * The named types can only be constructed explicitly and used as parameters for functions to avoid
 * ambiguity errors.
 *
 * @snippet test/var.test.cpp var_ctor_default
 *
 * @tparam T the type of the contained value
 */
template <typename T>
class var {
public:
    explicit var(T&& value) noexcept;
    explicit var(const T& value) noexcept;

    var() noexcept = default;
    ~var() = default;
    var(var&&) noexcept = default;
    var(const var&) noexcept = default;
    auto operator=(var&&) noexcept -> var& = default;
    auto operator=(const var&) noexcept -> var& = default;

    explicit operator T&() noexcept;
    explicit operator const T&() const noexcept;

    auto get() noexcept -> T&;
    auto get() const noexcept -> const T&;

private:
    T value_;
};

template <typename T>
var<T>::var(T&& value) noexcept : value_(std::move(value)) {}

template <typename T>
var<T>::var(const T& value) noexcept : value_(value) {}

template <typename T>
var<T>::operator T&() noexcept {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<T&>(const_cast<const var*>(this)->operator T&());
}

template <typename T>
var<T>::operator const T&() const noexcept {
    return value_;
}

template <typename T>
auto var<T>::get() noexcept -> T& {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast) @see Effective C++ by Scott Meyers
    return const_cast<T&>(const_cast<const var*>(this)->get());
}

template <typename T>
auto var<T>::get() const noexcept -> const T& {
    return value_;
}

}  // namespace util

#endif  // THAT_THIS_UTIL_VAR_HEADER_HEADER_FILE_IS_ALREADY_INCLUDED
