# util

[![Travis](https://travis-ci.com/sourcechris/util.svg?branch=master)](https://travis-ci.com/sourcechris/util)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/sourcechris/util/master/LICENSE.MIT)

This  library is a collection of utility classes and functions for C++. It is a "best of the rest" collection of 
independent self-contained headers. This means you can just copy-paste individuak header files from this library and use
them in your project without additional setup.

## How to build

This library builds with CMake. It is recommended to do an out-of-source build. Create a new directory and run CMake to 
generate the responsible make files.

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

You can run the util tests from the project via CMake.By default, the tests are built with CMake. After building, you 
can run the tests via the ctest command.

```sh
ctest
```

There is a ctest case for each individual util header file.