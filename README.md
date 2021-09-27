# util

[![CI](https://github.com/mostsignificant/util/actions/workflows/cmake.yml/badge.svg)](https://github.com/mostsignificant/util/actions/workflows/cmake.yml)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/4f4313c1e1e047ca890edf1cc7c4137d)](https://www.codacy.com/gh/mostsignificant/util/dashboard?utm_source=github.com&utm_medium=referral&utm_content=mostsignificant/util&utm_campaign=Badge_Grade)
[![Documentation](http://readthedocs.org/projects/mostsignificantutil/badge/?version=latest)](https://mostsignificantutil.readthedocs.io/en/latest/?badge=latest)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/mostsignificant/util/master/LICENSE.MIT)

This library is a collection of utility classes and functions for C++. It is a collection of independent self-contained
headers. This means you can just copy-paste individual header files from this library and use them in your project
without additional setup.

## Features

### Data structures

- util::array
- util::buffer
- util::ring_buffer

### Iterators

- util::enumerate, a Python-like helper to iterate through a container and also have an index
- util::multirator, an iterate through go through several ranges together

### Utilities

- util::flags
- util::non_copyable and util::non_moveable
- util::sorted with util::sorted_vector, util::sorted_list etc.
- util::var
- util::ignore_unused

### Memory management

- util::guarded
- util::object
- util::scoped
- util::shared

## Usage

There are two versions of using the util library: individual headers or the whole library.
