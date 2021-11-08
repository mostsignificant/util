// SPDX-FileCopyrightText: 2021 Christian Göhring <mostsig@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef THAT_THIS_UTIL_RANGE_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_RANGE_HEADER_IS_ALREADY_INCLUDED

#include <utility>

namespace util {

/**
 * A helper class for creating Python-like ranges.
 */
template <class T>
class range_container {
public:
    class iterator;

    explicit range_container(T&& begin, T&& end, T&& step)
        : begin_value(std::move(begin)), end_value(std::move(end)), step_value(std::move(step)) {}

    auto begin() -> iterator;
    auto begin() const -> iterator;
    auto cbegin() const -> iterator;
    auto end() -> iterator;
    auto end() const -> iterator;
    auto cend() const -> iterator;

private:
    T begin_value{};
    T end_value{};
    T step_value{};
};

template <class T>
auto range(T&& end) -> range_container<T> {
    return range_container<T>(T{0}, std::move(end), T{1});
}

template <class T>
auto range(T&& begin, T&& end) -> range_container<T> {
    return range_container<T>(std::move(begin), std::move(end), T{1});
}

template <class T>
auto range(T&& begin, T&& end, T&& step) -> range_container<T> {
    return range_container<T>(std::move(begin), std::move(end), std::move(step));
}

template <class T>
class range_container<T>::iterator {
public:
    explicit iterator(const T& value, const T& step) : value(value), step(step) {}

    auto operator!=(const iterator& other) -> bool { return value < other.value; }

    auto operator++() -> iterator& {
        value += step;
        return *this;
    }

    auto operator*() const -> const T& { return value; }

private:
    T value;
    T step;
};

template <class T>
auto range_container<T>::begin() -> iterator {
    return iterator(begin_value, step_value);
}

template <class T>
auto range_container<T>::begin() const -> iterator {
    return iterator(begin_value, step_value);
}

template <class T>
auto range_container<T>::cbegin() const -> iterator {
    return iterator(begin_value, step_value);
}

template <class T>
auto range_container<T>::end() -> iterator {
    return iterator(end_value, step_value);
}

template <class T>
auto range_container<T>::end() const -> iterator {
    return iterator(end_value, step_value);
}

template <class T>
auto range_container<T>::cend() const -> iterator {
    return iterator(end_value, step_value);
}

}  // namespace util

#endif  // THAT_THIS_UTIL_RANGE_HEADER_IS_ALREADY_INCLUDED