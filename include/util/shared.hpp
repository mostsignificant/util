// SPDX-FileCopyrightText: 2021 Christian Göhring <mostsig@gmail.com>
// SPDX-License-Identifier: MIT

#ifndef THAT_THIS_UTIL_SHARED_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_SHARED_HEADER_IS_ALREADY_INCLUDED

namespace util {

template <class T>
class shared {
public:
private:
    std::size_t ref_ = 0;
};

}  // namespace util

#endif  // THAT_THIS_UTIL_SHARED_HEADER_IS_ALREADY_INCLUDED