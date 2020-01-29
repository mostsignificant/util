# util
This  library is a collection of utility classes and functions for C++. It is a "best of the rest" collection of independent headers.

## How to build

This library builds with CMake. It is recommended to do an out-of-source build. Create a new directory and run CMake to generate the responsible make files.

```sh
mkdir build
cd build
cmake ..
```

After creating the build files, you can run CMake with the build command.

```sh
cmake --build .
```

## How to use

There are two versions of using the util library: individual headers or the whole package.

## How to test

You can run the util tests from the project via CMake.