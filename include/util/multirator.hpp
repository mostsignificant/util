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

#pragma once

#include <cstddef>
#include <tuple>

/*
namespace util {
namespace stx {

    namespace detail {

        template <class... Iterators, std::size_t... I>
        inline auto
        make_reference_tuple(std::tuple<Iterators...>& iterators,
std::index_sequence<I...>) { return std::tuple<typename
Iterators::reference...>(std::get<I>(iterators).operator*()...);
        }

        template <class... Iterators, std::size_t... I>
        inline auto
        iterator_tuple_neq(const std::tuple<Iterators...>& lhs, const
std::tuple<Iterators...>& rhs, std::index_sequence<I...>) { return
((std::get<I>(lhs) != std::get<I>(rhs)) && ...);
        }

        template<class... Containers, std::size_t... I>
        inline auto
        make_const_iterator_begin_tuple(const std::tuple<const Containers*...>&
containers, std::index_sequence<I...>) { return std::tuple<typename
Containers::const_iterator...>(begin(*std::get<I>(containers))...);
        }

        template<class... Containers, std::size_t... I>
        inline auto
        make_const_iterator_end_tuple(const std::tuple<const Containers*...>&
containers, std::index_sequence<I...>) { return std::tuple<typename
Containers::const_iterator...>(end(*std::get<I>(containers))...);
        }

    }

    template <class... Iterators>
    class multirator
    {
    public:
        using value_type      = std::tuple<typename Iterators::reference...>;
        using reference       = std::tuple<typename Iterators::reference...>&;
        using const_reference = const std::tuple<typename
Iterators::reference...>&;    namespace detail {

        using std::swap;

        template <class T, class U>
        using swappable_t = decltype(swap(std::declval<T>(),
std::declval<U>()));

        template <class T, class U>
        using is_swappable_with = is_detected_exact<bool, swappable_t, T, U>;

        template <class T>
        using is_swappable = is_swappable_with<T&, T&>;

        template <class T>
        using iterator_traits_value_type_t = typename
std::iterator_traits<T>::value_type;

        template <class T>
        using has_iterator_traits_value_type =
is_detected<iterator_traits_value_type_t, T>;

        template<class T>
        using iterator_traits_difference_type_t = typename
std::iterator_traits<T>::difference_type;

        template<class T>
        using has_iterator_traits_difference_type =
is_detected<iterator_traits_difference_type_t, T>;

        template<class T>
        using iterator_traits_reference_t = typename
std::iterator_traits<T>::reference;

        template<class T>
        using has_iterator_traits_reference =
is_detected<iterator_traits_reference_t, T>;

        template<class T>
        using iterator_traits_pointer_t = typename
std::iterator_traits<T>::pointer;

        template<class T>
        using has_iterator_traits_pointer =
is_detected<iterator_traits_pointer_t, T>;

        template<class T>
        using iterator_traits_iterator_category_t = typename
std::iterator_traits<T>::iterator_category;

        template<class T>
        using has_iterator_traits_iterator_category =
is_detected<iterator_traits_iterator_category_t, T>;

        template<class T>
        using pre_increment_operator_t = decltype(++std::declval<T>());

        template<class T>
        using has_pre_increment_operator = is_detected_exact<T&,
pre_increment_operator_t, T>;

        template<class T>
        using dereference_operator_t = decltype(*std::declval<T>());

        template<class T>
        using has_dereference_operator = is_detected<dereference_operator_t, T>;

    }

}

        multirator(Iterators... iterators) :
            iterators(iterators...) {}

        multirator(std::tuple<Iterators...> iterator_tuple) :
                iterators(iterator_tuple) {}

        multirator& operator++() {
            std::apply([&](auto&... it) { ((it++), ...); }, iterators);
            return *this;
        }

        multirator& operator+(int i) {
            std::apply([&](auto&... it) { ((it += i), ...); }, iterators);
            return *this;
        }

        bool operator!=(const multirator& other) const noexcept {
            return detail::iterator_tuple_neq(iterators, other.iterators,
std::index_sequence_for<Iterators...>{});
        }

        reference operator*() noexcept {
            auto tuple = detail::make_reference_tuple(iterators,
std::index_sequence_for<Iterators...>{});
            std::memcpy(static_cast<void*>(&values[0]), static_cast<const
void*>(&tuple), sizeof(value_type)); return reinterpret_cast<reference>(values);
        }

        const_reference operator*() const noexcept {
            auto tuple = detail::make_reference_tuple(iterators,
std::index_sequence_for<Iterators...>{});
            std::memcpy(static_cast<void*>(&values[0]), static_cast<const
void*>(&tuple), sizeof(value_type)); return
reinterpret_cast<const_reference>(values);
        }

    private:
        std::tuple<Iterators...> iterators;
        uint8_t values[sizeof(value_type)];
    };

    template<class... Containers>
    class const_multirator_range
    {
    public:
        using const_iterator = multirator<typename
Containers::const_iterator...>;

        const_multirator_range(const Containers&... containers) :
                const_containers(std::addressof(containers)...) {
        }

        const_iterator
        begin() const {
            return
const_iterator(detail::make_const_iterator_begin_tuple(const_containers,
                                                                          std::index_sequence_for<Containers...>{}));
        };

        const_iterator
        end() const {
            return
const_iterator(detail::make_const_iterator_end_tuple(const_containers,
                                                                        std::index_sequence_for<Containers...>{}));
};

    private:
        std::tuple<const Containers*...> const_containers;
    };

    template<class Container, class... Containers>
    class multirator_range : public const_multirator_range<Container,
Containers...>
    {
    public:
        using iterator = multirator<typename Container::iterator, typename
Containers::iterator...>; using const_iterator = typename
const_multirator_range<Container, Containers...>::const_iterator;

        multirator_range(Container& container, Containers&... containers) :
            containers(std::addressof(container), std::addressof(containers)...)
{
        }

        iterator begin();
        iterator end();
        const_iterator cbegin();
        const_iterator cend();

    private:
        std::tuple<Container*, Containers*...> containers;
    };

    template<class... Containers>
    inline auto make_multirator_range(Containers&... containers) {
        return multirator_range(containers...);
    }

    template<class... Containers>
    inline auto make_multirator_range(const Containers&... containers) {
        return const_multirator_range(containers...);
    }

}
}

*/