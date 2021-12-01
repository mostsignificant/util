// SPDX-FileCopyrightText: 2021 Christian Göhring <mostsig@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef THAT_THIS_UTIL_COLOR_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_COLOR_HEADER_IS_ALREADY_INCLUDED

#include <cstdint>
#include <limits>

namespace util {

template <class T = std::uint8_t>
class color {
public:
    color(T red, T green, T blue);
    color(T red, T green, T blue, T alpha);
    color(T red, T green, T blue, float alpha);
    color(float red, float green, float blue);
    color(float red, float green, float blue, T alpha);
    color(float red, float green, float blue, float alpha);

    ~color() = default;
    color(const color&) = default;
    color(color&&) = default;
    auto operator=(const color&) noexcept -> color& = default;
    auto operator=(color&&) noexcept -> color& = default;

    static auto from_rgb(T red, T green, T blue) -> color;
    static auto from_rgba(T red, T green, T blue, T alpha) -> color;
    static auto from_rgba(T red, T green, T blue, float alpha) -> color;
    static auto from_rgb(float red, float green, float blue) -> color;
    static auto from_rgba(float red, float green, float blue, T alpha) -> color;
    static auto from_rgba(float red, float green, float blue, float alpha) -> color;

    auto get_red() const noexcept -> T;
    auto get_green() const noexcept -> T;
    auto get_blue() const noexcept -> T;
    auto get_alpha() const noexcept -> T;
    auto get_red_as_float() const noexcept -> float;
    auto get_green_as_float() const noexcept -> float;
    auto get_blue_as_float() const noexcept -> float;
    auto get_alpha_as_float() const noexcept -> float;

private:
    T red = 0;
    T green = 0;
    T blue = 0;
    T alpha = 0;
};

template <class T>
color<T>::color(T red, T green, T blue) : color(red, green, blue, static_cast<T>(0)) {}

template <class T>
color<T>::color(T red, T green, T blue, T alpha)
    : red(red), green(green), blue(blue), alpha(alpha) {}

template <class T>
color<T>::color(T red, T green, T blue, float alpha)
    : color(red, green, blue, static_cast<T>(alpha * std::numeric_limits<T>::max())) {}

template <class T>
color<T>::color(float red, float green, float blue)
    : color(static_cast<T>(red * std::numeric_limits<T>::max()),
            static_cast<T>(green * std::numeric_limits<T>::max()),
            static_cast<T>(blue * std::numeric_limits<T>::max()), static_cast<T>(0)) {}

template <class T>
color<T>::color(float red, float green, float blue, T alpha)
    : color(static_cast<T>(red * std::numeric_limits<T>::max()),
            static_cast<T>(green * std::numeric_limits<T>::max()),
            static_cast<T>(blue * std::numeric_limits<T>::max()), alpha) {}

template <class T>
color<T>::color(float red, float green, float blue, float alpha)
    : color(static_cast<T>(red * std::numeric_limits<T>::max()),
            static_cast<T>(green * std::numeric_limits<T>::max()),
            static_cast<T>(blue * std::numeric_limits<T>::max()),
            static_cast<T>(alpha * std::numeric_limits<T>::max())) {}

template <class T>
auto color<T>::from_rgb(T red, T green, T blue) -> color {
    return {red, green, blue};
}

template <class T>
auto color<T>::from_rgba(T red, T green, T blue, T alpha) -> color {
    return {red, green, blue, alpha};
}

template <class T>
auto color<T>::from_rgba(T red, T green, T blue, float alpha) -> color {
    return {red, green, blue, alpha};
}

template <class T>
auto color<T>::from_rgb(float red, float green, float blue) -> color {
    return {red, green, blue};
}

template <class T>
auto color<T>::from_rgba(float red, float green, float blue, T alpha) -> color {
    return {red, green, blue, alpha};
}

template <class T>
auto color<T>::from_rgba(float red, float green, float blue, float alpha) -> color {
    return {red, green, blue, alpha};
}

template <class T>
auto color<T>::get_red() const noexcept -> T {
    return red;
}

template <class T>
auto color<T>::get_green() const noexcept -> T {
    return green;
}

template <class T>
auto color<T>::get_blue() const noexcept -> T {
    return blue;
}

template <class T>
auto color<T>::get_alpha() const noexcept -> T {
    return alpha;
}

template <class T>
auto color<T>::get_red_as_float() const noexcept -> float {
    return red;
}

template <class T>
auto color<T>::get_green_as_float() const noexcept -> float {
    return green;
}

template <class T>
auto color<T>::get_blue_as_float() const noexcept -> float {
    return blue;
}

template <class T>
auto color<T>::get_alpha_as_float() const noexcept -> float {
    return alpha;
}

}  // namespace util

#endif  // THAT_THIS_UTIL_COLOR_HEADER_IS_ALREADY_INCLUDED
