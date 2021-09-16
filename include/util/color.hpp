#ifndef THAT_THIS_UTIL_COLOR_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_COLOR_HEADER_IS_ALREADY_INCLUDED

#include <cstdint>
#include <limits>

namespace util {

class color {
public:
    color(uint8_t red, uint8_t green, uint8_t blue);
    color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    color(uint8_t red, uint8_t green, uint8_t blue, float alpha);
    color(float red, float green, float blue);
    color(float red, float green, float blue, uint8_t alpha);
    color(float red, float green, float blue, float alpha);

    ~color() = default;
    color(const color&) = default;
    color(color&&) = default;
    auto operator=(const color&) -> color& = default;
    auto operator=(color&&) -> color& = default;

    static auto from_rgb(uint8_t red, uint8_t green, uint8_t blue) -> color;
    static auto from_rgba(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) -> color;
    static auto from_rgba(uint8_t red, uint8_t green, uint8_t blue, float alpha) -> color;
    static auto from_rgb(float red, float green, float blue) -> color;
    static auto from_rgba(float red, float green, float blue, uint8_t alpha) -> color;
    static auto from_rgba(float red, float green, float blue, float alpha) -> color;

    auto get_red() const noexcept -> uint8_t;
    auto get_green() const noexcept -> uint8_t;
    auto get_blue() const noexcept -> uint8_t;
    auto get_alpha() const noexcept -> uint8_t;
    auto get_red_as_float() const noexcept -> float;
    auto get_green_as_float() const noexcept -> float;
    auto get_blue_as_float() const noexcept -> float;
    auto get_alpha_as_float() const noexcept -> float;

private:
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    uint8_t alpha = 0;
};

color::color(uint8_t red, uint8_t green, uint8_t blue)
    : color(red, green, blue, static_cast<uint8_t>(0)) {}

color::color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
    : red(red), green(green), blue(blue), alpha(alpha) {}

color::color(uint8_t red, uint8_t green, uint8_t blue, float alpha)
    : color(red, green, blue, static_cast<uint8_t>(alpha * std::numeric_limits<uint8_t>::max())) {}

color::color(float red, float green, float blue)
    : color(static_cast<uint8_t>(red * std::numeric_limits<uint8_t>::max()),
            static_cast<uint8_t>(green * std::numeric_limits<uint8_t>::max()),
            static_cast<uint8_t>(blue * std::numeric_limits<uint8_t>::max()),
            static_cast<uint8_t>(0)) {}

color::color(float red, float green, float blue, uint8_t alpha)
    : color(static_cast<uint8_t>(red * std::numeric_limits<uint8_t>::max()),
            static_cast<uint8_t>(green * std::numeric_limits<uint8_t>::max()),
            static_cast<uint8_t>(blue * std::numeric_limits<uint8_t>::max()), alpha) {}

color::color(float red, float green, float blue, float alpha)
    : color(static_cast<uint8_t>(red * std::numeric_limits<uint8_t>::max()),
            static_cast<uint8_t>(green * std::numeric_limits<uint8_t>::max()),
            static_cast<uint8_t>(blue * std::numeric_limits<uint8_t>::max()),
            static_cast<uint8_t>(alpha * std::numeric_limits<uint8_t>::max())) {}

auto color::from_rgb(uint8_t red, uint8_t green, uint8_t blue) -> color {
    return {red, green, blue};
}

auto color::from_rgba(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) -> color {
    return {red, green, blue, alpha};
}

auto color::from_rgba(uint8_t red, uint8_t green, uint8_t blue, float alpha) -> color {
    return {red, green, blue, alpha};
}

auto color::from_rgb(float red, float green, float blue) -> color { return {red, green, blue}; }

auto color::from_rgba(float red, float green, float blue, uint8_t alpha) -> color {
    return {red, green, blue, alpha};
}

auto color::from_rgba(float red, float green, float blue, float alpha) -> color {
    return {red, green, blue, alpha};
}

auto color::get_red() const noexcept -> uint8_t { return red; }

auto color::get_green() const noexcept -> uint8_t { return green; }

auto color::get_blue() const noexcept -> uint8_t { return blue; }

auto color::get_alpha() const noexcept -> uint8_t { return alpha; }

auto color::get_red_as_float() const noexcept -> float { return red; }

auto color::get_green_as_float() const noexcept -> float { return green; }

auto color::get_blue_as_float() const noexcept -> float { return blue; }

auto color::get_alpha_as_float() const noexcept -> float { return alpha; }

}  // namespace util

#endif  // THAT_THIS_UTIL_COLOR_HEADER_IS_ALREADY_INCLUDED
