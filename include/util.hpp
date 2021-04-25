#ifndef THAT_THIS_UTIL_HEADER_FILE_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_HEADER_FILE_IS_ALREADY_INCLUDED

namespace util {

using int8 = char;
using int16 = short;
using int32 = int;
using int64 = long long;
using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;
using size_t = unsigned long long;

struct out_of_range {};

template <class T>
struct initializer_list {};

}  // namespace util

#endif  // THAT_THIS_UTIL_HEADER_FILE_IS_ALREADY_INCLUDED