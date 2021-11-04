// SPDX-FileCopyrightText: 2021 Christian Göhring <mostsig@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef THAT_THIS_UTIL_MULTIRATOR_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_MULTIRATOR_HEADER_IS_ALREADY_INCLUDED

#include <array>
#include <cstddef>
#include <cstring>
#include <iterator>
#include <tuple>

namespace util {

namespace detail {

template <class... Iterators, std::size_t... I>
auto make_reference_tuple(std::tuple<Iterators...>& iterators, std::index_sequence<I...>);

template <class... Iterators, std::size_t... I>
auto iterator_tuple_neq(const std::tuple<Iterators...>& lhs, const std::tuple<Iterators...>& rhs,
                        std::index_sequence<I...>);

template <class... Containers, std::size_t... I>
auto make_const_iterator_begin_tuple(const std::tuple<const Containers*...>& containers,
                                     std::index_sequence<I...>);

template <class... Containers, std::size_t... I>
auto make_const_iterator_end_tuple(const std::tuple<const Containers*...>& containers,
                                   std::index_sequence<I...>);

template <class... Containers, std::size_t... I>
auto make_iterator_begin_tuple(const std::tuple<Containers*...>& containers,
                               std::index_sequence<I...>);

template <class... Containers, std::size_t... I>
auto make_iterator_end_tuple(const std::tuple<Containers*...>& containers,
                             std::index_sequence<I...>);

}  // namespace detail

template <class... Iterators>
class multirator {
public:
    using value_type = std::tuple<typename Iterators::reference...>;
    using reference = std::tuple<typename Iterators::reference...>&;
    using const_reference = const std::tuple<typename Iterators::reference...>&;

    explicit multirator(Iterators... iterators) : iterators(iterators...) {}

    explicit multirator(std::tuple<Iterators...> iterator_tuple) : iterators(iterator_tuple) {}

    auto operator++() -> multirator& {
        std::apply([&](auto&... it) { ((it++), ...); }, iterators);
        return *this;
    }

    auto operator+(int i) -> multirator& {
        std::apply([&](auto&... it) { ((it += i), ...); }, iterators);
        return *this;
    }

    auto operator!=(const multirator& other) const noexcept -> bool {
        return detail::iterator_tuple_neq(iterators, other.iterators,
                                          std::index_sequence_for<Iterators...>{});
    }

    auto operator*() noexcept -> reference {
        auto tuple =
            detail::make_reference_tuple(iterators, std::index_sequence_for<Iterators...>{});
        std::memcpy(static_cast<void*>(&values[0]), static_cast<const void*>(&tuple),
                    sizeof(value_type));
        return reinterpret_cast<reference>(values);
    }

    auto operator*() const noexcept -> const_reference {
        auto tuple =
            detail::make_reference_tuple(iterators, std::index_sequence_for<Iterators...>{});
        std::memcpy(static_cast<void*>(&values[0]), static_cast<const void*>(&tuple),
                    sizeof(value_type));
        return reinterpret_cast<const_reference>(values);
    }

private:
    std::tuple<Iterators...> iterators;
    std::array<uint8_t, sizeof(value_type)> values;
};

template <class... Containers>
class const_multirator_range {
public:
    using const_iterator = multirator<typename Containers::const_iterator...>;

    explicit const_multirator_range(const Containers&... containers);

    auto begin() const -> const_iterator;
    auto end() const -> const_iterator;

private:
    std::tuple<const Containers*...> const_containers;
};

template <class... Containers>
class multirator_range {
    static constexpr bool Const = std::is_const_v<Containers...>;

public:
    using iterator = multirator<typename Containers::iterator...>;
    using const_iterator = typename const_multirator_range<Containers...>::const_iterator;

    explicit multirator_range(Containers&... containers);

    auto begin() -> iterator;
    auto end() -> iterator;
    auto cbegin() -> const_iterator;
    auto cend() -> const_iterator;

private:
    std::tuple<Containers*...> containers;
};

template <class... Containers>
const_multirator_range<Containers...>::const_multirator_range(const Containers&... containers)
    : const_containers(std::addressof(containers)...) {}

template <class... Containers>
auto const_multirator_range<Containers...>::begin() const -> const_iterator {
    return const_iterator(detail::make_const_iterator_begin_tuple(
        const_containers, std::index_sequence_for<Containers...>{}));
};

template <class... Containers>
auto const_multirator_range<Containers...>::end() const -> const_iterator {
    return const_iterator(detail::make_const_iterator_end_tuple(
        const_containers, std::index_sequence_for<Containers...>{}));
};

template <class... Containers>
multirator_range<Containers...>::multirator_range(Containers&... containers)
    : containers(std::addressof(containers)...) {}

template <class... Containers>
auto multirator_range<Containers...>::begin() -> iterator {
    return iterator(
        detail::make_iterator_begin_tuple(containers, std::index_sequence_for<Containers...>{}));
}

template <class... Containers>
auto multirator_range<Containers...>::end() -> iterator {
    return iterator(
        detail::make_iterator_end_tuple(containers, std::index_sequence_for<Containers...>{}));
}

template <class... Containers>
auto multirator_range<Containers...>::cbegin() -> const_iterator {
    return const_iterator(detail::make_const_iterator_begin_tuple(
        containers, std::index_sequence_for<Containers...>{}));
}

template <class... Containers>
auto multirator_range<Containers...>::cend() -> const_iterator {
    return const_iterator(detail::make_const_iterator_end_tuple(
        containers, std::index_sequence_for<Containers...>{}));
}

template <class... Containers>
auto make_multirator_range(Containers&... containers) {
    return multirator_range(containers...);
}

template <class... Containers>
auto make_multirator_range(const Containers&... containers) {
    return const_multirator_range(containers...);
}

template <class... Iterators, std::size_t... I>
auto detail::make_reference_tuple(std::tuple<Iterators...>& iterators, std::index_sequence<I...>) {
    return std::tuple<typename Iterators::reference...>(std::get<I>(iterators).operator*()...);
}

template <class... Iterators, std::size_t... I>
auto detail::iterator_tuple_neq(const std::tuple<Iterators...>& lhs,
                                const std::tuple<Iterators...>& rhs, std::index_sequence<I...>) {
    return ((std::get<I>(lhs) != std::get<I>(rhs)) && ...);
}

template <class... Containers, std::size_t... I>
auto detail::make_const_iterator_begin_tuple(const std::tuple<const Containers*...>& containers,
                                             std::index_sequence<I...>) {
    return std::tuple<typename Containers::const_iterator...>(begin(*std::get<I>(containers))...);
}

template <class... Containers, std::size_t... I>
auto detail::make_const_iterator_end_tuple(const std::tuple<const Containers*...>& containers,
                                           std::index_sequence<I...>) {
    return std::tuple<typename Containers::const_iterator...>(end(*std::get<I>(containers))...);
}

template <class... Containers, std::size_t... I>
auto detail::make_iterator_begin_tuple(const std::tuple<Containers*...>& containers,
                                       std::index_sequence<I...>) {
    return std::tuple<typename Containers::iterator...>(begin(*std::get<I>(containers))...);
}

template <class... Containers, std::size_t... I>
auto detail::make_iterator_end_tuple(const std::tuple<Containers*...>& containers,
                                     std::index_sequence<I...>) {
    return std::tuple<typename Containers::iterator...>(end(*std::get<I>(containers))...);
}

}  // namespace util

#endif  // THAT_THIS_UTIL_MULTIRATOR_HEADER_IS_ALREADY_INCLUDED