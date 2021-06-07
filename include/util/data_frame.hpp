#ifndef THAT_THIS_UTIL_DATA_FRAME_HEADER_IS_ALREADY_INCLUDED
#define THAT_THIS_UTIL_DATA_FRAME_HEADER_IS_ALREADY_INCLUDED

#include <vector>

namespace util {

/**
 * Two-dimensional tabular data container.
 */
template <class T, class Allocator = std::allocator<T>>
class data_frame {
public:
    using value_type = T;
    using iterator = value_type*;

    enum axis { index, column };

private:
    std::vector<T, Allocator> data;
};

}  // namespace util

#endif
