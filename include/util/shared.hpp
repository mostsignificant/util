// SPDX-FileCopyrightText: 2021 Christian Göhring <mostsig@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef THAT_THIS_UTIL_SHARED_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_SHARED_HEADER_IS_ALREADY_INCLUDED

#include <cstddef>

namespace util {

template <class T>
class shared {
public:
    constexpr shared() = default;
    constexpr shared(std::nullptr_t) noexcept;
    shared(T* ptr) noexcept;
    shared(shared&& other) noexcept;
    shared(const shared& other);
    ~shared();

    auto operator=(shared&& other) noexcept -> shared&;
    auto operator=(const shared& other) -> shared&;

    auto operator->() const noexcept -> T*;
    auto operator*() const noexcept -> T&;
    explicit operator bool() const noexcept;

    auto get() const noexcept -> T*;
    auto use_count() const noexcept -> std::size_t;

private:
    T* ptr = nullptr;
    std::size_t* ref = new std::size_t(0);
};

template <class T>
constexpr shared<T>::shared(std::nullptr_t) noexcept : shared() {}

template <class T>
shared<T>::shared(T* ptr) noexcept : ptr(ptr), ref(new std::size_t(1)) {}

template <class T>
shared<T>::~shared() {
    (*this->ref)--;
    if (*this->ref == 0) {
        delete this->ptr;
        delete this->ref;
    }
}

template <class T>
shared<T>::shared(shared&& other) noexcept {
    this->ptr = other.ptr;
    this->ref = other.ref;
    other.ptr = nullptr;
    other.ref = nullptr;
}

template <class T>
shared<T>::shared(const shared& other) {
    this->ptr = other.ptr;
    this->ref = other.ref;
    if (other.ptr) {
        (*this->ref)++;
    }
}

template <class T>
auto shared<T>::operator=(shared&& other) noexcept -> shared<T>& {
    this->ptr = other.ptr;
    this->ref = other.ref;
    other.ptr = nullptr;
    other.ref = nullptr;

    return *this;
}

template <class T>
auto shared<T>::operator=(const shared& other) -> shared<T>& {
    this->ptr = other.ptr;
    this->ref = other.ref;
    if (other.ptr) {
        (*this->ref)++;
    }

    return *this;
}

template <class T>
auto shared<T>::operator->() const noexcept -> T* {
    return this->ptr;
}

template <class T>
auto shared<T>::operator*() const noexcept -> T& {
    return *this->ptr;
}

template <class T>
shared<T>::operator bool() const noexcept {
    return this->ptr != nullptr;
}

template <class T>
auto shared<T>::get() const noexcept -> T* {
    return this->ptr;
}

template <class T>
auto shared<T>::use_count() const noexcept -> std::size_t {
    return *this->ref;
}

}  // namespace util

#endif  // THAT_THIS_UTIL_SHARED_HEADER_IS_ALREADY_INCLUDED