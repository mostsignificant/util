# Compiler flags

The util library offers certain compiler flags for additional features. These compiler flags can only be used if the
whole project is included since the central `util.hpp` header file is needed.

## UTIL_ASSERT

This compiler flags enables the throwing of a util_assertion on certain functions, for example accessing a nullptr. The
corresponding function's documentation describes explicitly if it throws an assertion. This feature is useful for
tracking down problems in debug builds. It is recommended to use this compiler flag only during testing with debug
builds.
