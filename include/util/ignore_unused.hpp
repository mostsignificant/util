

namespace util {

/**
 * Helper function for ignoring warnings about unused variables.
 *
 * @snippet test/ignore_unused.test.cpp ignore_unused_function
 */
template <typename... Ts>
void ignore_unused(Ts&&... ts) noexcept {}

}  // namespace util