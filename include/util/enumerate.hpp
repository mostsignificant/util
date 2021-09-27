#ifndef THAT_THIS_UTIL_DATA_ENUMERATE_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_DATA_ENUMERATE_HEADER_IS_ALREADY_INCLUDED

#include <cstddef>
#include <iterator>
#include <utility>

namespace util {

/**
 * A helper class for Python-like enumerating through the elements of a container.
 *
 * @tparam Container the type of container used in this range
 */
template <class Container>
struct enumerate_range {
    static constexpr bool Const = std::is_const_v<Container>;

    class iterator {
    public:
        using size_type = typename Container::size_type;
        using value_type = typename Container::value_type;
        using pointer = typename std::conditional_t<Const, const value_type*, value_type*>;
        using reference = typename std::conditional_t<Const, const value_type&, value_type&>;
        using container_iterator =
            typename std::conditional_t<Const, typename Container::const_iterator,
                                        typename Container::iterator>;

        struct pair {
            size_type pos;
            reference ref;
        };

        iterator(container_iterator iterator);

        auto operator!=(const iterator& other) -> bool;
        auto operator++() -> iterator&;
        auto operator*() const -> pair;

    private:
        container_iterator it;
        size_type pos = 0;
    };

    using container_reference = Container&;

    explicit enumerate_range(container_reference container);

    auto begin() -> iterator;
    auto end() -> iterator;

private:
    container_reference container;
};

template <class Container>
auto enumerate(Container& container) -> enumerate_range<Container> {
    return enumerate_range<Container>(container);
}

template <class Container>
enumerate_range<Container>::enumerate_range(container_reference container) : container(container) {}

template <class Container>
auto enumerate_range<Container>::begin() -> iterator {
    return iterator(container.begin());
}

template <class Container>
auto enumerate_range<Container>::end() -> iterator {
    return iterator(container.end());
}

template <class Container>
enumerate_range<Container>::iterator::iterator(container_iterator iterator)
    : it(iterator), pos(0) {}

template <class Container>
auto enumerate_range<Container>::iterator::operator!=(const iterator& other) -> bool {
    return it != other.it;
}

template <class Container>
auto enumerate_range<Container>::iterator::operator++() -> iterator& {
    it++;
    pos++;
    return *this;
}

template <class Container>
auto enumerate_range<Container>::iterator::operator*() const -> pair {
    return pair{pos, *it};
}

}  // namespace util

#endif  // THAT_THIS_UTIL_DATA_ENUMERATE_HEADER_IS_ALREADY_INCLUDED