#ifndef THAT_THIS_UTIL_DATA_ENUMERATE_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_DATA_ENUMERATE_HEADER_IS_ALREADY_INCLUDED

#include <cstddef>
#include <iterator>
#include <utility>

namespace util {

template <class Iter, class T, bool Const = false>
class enumerate_iterator {
public:
    using pointer = typename std::conditional_t<Const, const T* const, T*>;
    using reference = typename std::conditional_t<Const, const T&, T&>;

    enumerate_iterator(Iter iterator, std::size_t pos);

    auto operator!=(const enumerate_iterator& other) -> bool;
    void operator++();
    auto operator*() const -> std::pair<std::size_t, reference>;

private:
    Iter iterator;
    std::size_t pos;
};

template <class Container, bool Const = false>
struct enumerate_range {
    using container_iterator = typename Container::iterator;
    using container_const_iterator = typename Container::const_iterator;
    using value_type = typename Container::value_type;
    using iterator = enumerate_iterator<container_iterator, value_type, Const>;
    using const_iterator = enumerate_iterator<container_const_iterator, value_type, Const>;
    using reference = typename std::conditional_t<Const, const Container&, Container&>;

    explicit enumerate_range(reference container);

    enumerate_range() = delete;

    //  auto begin() -> iterator;
    auto begin() const -> const_iterator;
    auto cbegin() -> const_iterator;
    // auto end() -> iterator;
    auto end() const -> const_iterator;
    auto cend() -> const_iterator;

private:
    reference container;
};

template <class Container>
auto enumerate(const Container& container) -> enumerate_range<Container, true> {
    return enumerate_range<Container, true>(container);
}

template <class Container>
auto enumerate(Container& container) -> enumerate_range<Container, false> {
    return enumerate_range<Container, false>(container);
}

template <class Container, bool Const>
enumerate_range<Container, Const>::enumerate_range(reference container) : container(container) {}

template <class Container, bool Const>
auto enumerate_range<Container, Const>::begin() const -> const_iterator {
    return const_iterator(container.begin(), 0);
}

template <class Container, bool Const>
auto enumerate_range<Container, Const>::cbegin() -> const_iterator {
    return const_iterator(container.begin(), 0);
}

template <class Container, bool Const>
auto enumerate_range<Container, Const>::end() const -> const_iterator {
    return const_iterator(container.end(), std::distance(container.begin(), container.end()));
}

template <class Container, bool Const>
auto enumerate_range<Container, Const>::cend() -> const_iterator {
    return const_iterator(container.end(), std::distance(container.begin(), container.end()));
}

template <class Iter, class T, bool Const>
enumerate_iterator<Iter, T, Const>::enumerate_iterator(Iter iterator, std::size_t pos)
    : iterator(iterator), pos(pos) {}

template <class Iter, class T, bool Const>
auto enumerate_iterator<Iter, T, Const>::operator!=(const enumerate_iterator& other) -> bool {
    return iterator != other.iterator;
}

template <class Iter, class T, bool Const>
void enumerate_iterator<Iter, T, Const>::operator++() {
    iterator++;
    pos++;
}

template <class Iter, class T, bool Const>
auto enumerate_iterator<Iter, T, Const>::operator*() const -> std::pair<std::size_t, reference> {
    return std::pair<std::size_t, reference>{pos, *iterator};
}

}  // namespace util

#endif  // THAT_THIS_UTIL_DATA_ENUMERATE_HEADER_IS_ALREADY_INCLUDED