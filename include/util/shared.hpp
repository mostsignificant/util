// SPDX-FileCopyrightText: 2021 Christian Göhring <mostsig@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef THAT_THIS_UTIL_SHARED_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_SHARED_HEADER_IS_ALREADY_INCLUDED

#include <cstddef>
#include <utility>

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

template <class T, class... Args>
auto make_shared(Args&&... args) -> shared<T>;

/**
 * Constructs a shared object from a nullpointer.
 */
template <class T>
constexpr shared<T>::shared(std::nullptr_t) noexcept : shared() {}

/**
 * Constructs a shared object from a given pointer.
 */
template <class T>
shared<T>::shared(T* ptr) noexcept : ptr(ptr), ref(new std::size_t(1)) {}

/**
 * Destroys a shared object instance and decreases the reference counter. If the reference counter
 * reaches zero (i.e. this is the last reference to the managed instance) then the managed instance
 * will be deleted.
 */
template <class T>
shared<T>::~shared() {
    (*this->ref)--;

    if (*this->ref == 0) {
        delete this->ptr;
        delete this->ref;
    }
}

/**
 * Constructs a shared instance from another moved shared instance. The moved instance's pointer and
 * reference counter are unassigned.
 *
 * @param other another shared instance
 */
template <class T>
shared<T>::shared(shared&& other) noexcept {
    this->ptr = other.ptr;
    this->ref = other.ref;
    other.ptr = nullptr;
    other.ref = nullptr;
}

/**
 * Constructs a shared instance from another shared instance.
 *
 * @param other another shared instance
 */
template <class T>
shared<T>::shared(const shared& other) {
    this->ptr = other.ptr;
    this->ref = other.ref;

    if (other.ptr) {
        (*this->ref)++;
    }
}

/**
 * Assigns a moved shared instance. The moved instance's pointer and reference counter are
 * unassigned.
 *
 * @return a reference to this instance
 */
template <class T>
auto shared<T>::operator=(shared&& other) noexcept -> shared<T>& {
    this->ptr = other.ptr;
    this->ref = other.ref;
    other.ptr = nullptr;
    other.ref = nullptr;

    return *this;
}

/**
 * Assigns a shared instance.
 *
 * @return a reference to this instance
 */
template <class T>
auto shared<T>::operator=(const shared& other) -> shared<T>& {
    if (this != &other) {
        (*this->ref)--;

        if (*this->ref == 0) {
            delete this->ptr;
            delete this->ref;
        }

        this->ptr = other.ptr;
        this->ref = other.ref;

        if (other.ptr) {
            (*this->ref)++;
        }
    }

    return *this;
}

/**
 * Returns the stored pointer.
 *
 * @return the stored pointer, i.e., `get()`
 */
template <class T>
auto shared<T>::operator->() const noexcept -> T* {
    return this->ptr;
}

/**
 * Returns the dereferenced managed object.
 *
 * @return the dereferenced stored pointer, i.e., `*get()`
 */
template <class T>
auto shared<T>::operator*() const noexcept -> T& {
    return *this->ptr;
}

/**
 * Checks if the stored pointer is not null.
 *
 * @return true if the stored pointer is null or false if not
 */
template <class T>
shared<T>::operator bool() const noexcept {
    return this->ptr != nullptr;
}

/**
 * Returns the stored pointer.
 *
 * @return the stored pointer
 */
template <class T>
auto shared<T>::get() const noexcept -> T* {
    return this->ptr;
}

/**
 * Returns the number of different shared_ptr instances (this included) managing the current object.
 * If there is no managed object, ​0​ is returned.
 *
 * @return the number of util::shared instances managing the current object or ​0​ if there is
 *         no managed object
 */
template <class T>
auto shared<T>::use_count() const noexcept -> std::size_t {
    return *this->ref;
}

/**
 * Constructs an object of type T and wraps it in a std::shared_ptr using args as the parameter list
 * for the constructor of T.
 *
 * @tparam T the type of object to construct
 * @tparam Args the types of arguments for the constructor of T
 * @param args a list of arguments with which an instance of T will be constructed
 * @return an util::shared object of an instance of type T
 */
template <class T, class... Args>
auto make_shared(Args&&... args) -> shared<T> {
    return shared<T>(new T(std::move(args...)));
}

}  // namespace util

#endif  // THAT_THIS_UTIL_SHARED_HEADER_IS_ALREADY_INCLUDED