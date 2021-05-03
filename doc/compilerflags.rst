Compiler flags
==============

The util library offers certain compiler flags for additional features. These compiler flags can only be used if the
whole project is included since the central `util.hpp` header file is needed.

UTIL_NO_STD_LIBRARY
-------------------

This flag allows the use of the util library without any C++ standard library dependencies. This might come in handy in
environments without C++ standard library or other restrictions.

UTIL_ASSERT
-----------

This compiler flags enables the throwing of a util::assertion on certain functions, for example accessing a nullptr. The
corresponding function's documentation describes explicitly if it throws an assertion. This feature is useful for
tracking down problems in debug builds. It is recommended to use this compiler flag only during testing with debug
builds.