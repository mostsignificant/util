/*
 * util - a collection of utility classes and functions for C++
 * <https://github.com/sourcechris/util>
 *
 * MIT License
 *
 * Copyright (c) 2020 Christian Göhring
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

#include <cstdint>

namespace util {

uint8_t  hton(uint8_t value);
uint16_t hton(uint16_t value);
uint32_t hton(uint32_t value);
uint64_t hton(uint64_t value);

uint8_t  ntoh(uint8_t value);
uint16_t ntoh(uint16_t value);
uint32_t ntoh(uint32_t value);
uint64_t ntoh(uint64_t value);

}  // namespace util

#if defined(WIN32) || defined(WIN64)
#include "Winsock2.h"
#else
#include <arpa/inet.h>
#endif

/**
 * Converts a 8-bit value from host to network byte order.
 *
 * @section test/endian.test.cpp HostToNetwork8bit
 *
 * @param value the 8-bit value in host byte order to convert
 * @return the value in network byte order
 */
uint8_t util::hton(uint8_t value) { return value; }

/**
 * Converts a 16-bit value from host to network byte order.
 *
 * @param value the 16-bit value in host byte order to convert
 * @return the value in network byte order
 */
uint16_t util::hton(uint16_t value) { return htons(value); }

/**
 * Converts a 32-bit value from host to network byte order.
 *
 * @param value the 32-bit value in host byte order to convert
 * @return the value in network byte order
 */
uint32_t util::hton(uint32_t value) { return htonl(value); }

/**
 * Converts a 64-bit value from host to network byte order.
 *
 * @param value the 64-bit value in host byte order to convert
 * @return the value in network byte order
 */
uint64_t util::hton(uint64_t value) {
    static const uint32_t num = 42U;

    if (*reinterpret_cast<const char*>(&num) == num) {
        const uint32_t hi = htonl(static_cast<uint32_t>(value >> 32));
        const uint32_t lo = htonl(static_cast<uint32_t>(value & 0xFFFFFFFFLL));
        return (static_cast<uint64_t>(lo) << 32) | hi;
    }

    return value;
}

/**
 * Converts a 8-bit value from network to host byte order.
 *
 * @param value the 8-bit value in host byte order to convert
 * @return the value in network byte order
 */
uint8_t util::ntoh(uint8_t value) { return value; }

/**
 * Converts a 16-bit value from network to host byte order.
 *
 * @param value the 16-bit value in host byte order to convert
 * @return the value in network byte order
 */
uint16_t util::ntoh(uint16_t value) { return ntohs(value); }

/**
 * Converts a 32-bit value from network to host byte order.
 *
 * @param value the 32-bit value in host byte order to convert
 * @return the value in network byte order
 */
uint32_t util::ntoh(uint32_t value) { return ntohl(value); }

/**
 * Converts a 64-bit value from network to host byte order.
 *
 * @param value the 64-bit value in host byte order to convert
 * @return the value in network byte order
 */
uint64_t util::ntoh(uint64_t value) {
    static const uint32_t num = 42U;

    if (*reinterpret_cast<const char*>(&num) == num) {
        const uint32_t hi = ntohl(static_cast<uint32_t>(value >> 32));
        const uint32_t lo = ntohl(static_cast<uint32_t>(value & 0xFFFFFFFFLL));
        return (static_cast<uint64_t>(lo) << 32) | hi;
    }

    return value;
}