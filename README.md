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

- util::buffer, a fixed-size data storage with additional dynamic storage if needed
- util::ring_buffer, a fixed-sized container behaving like an end-to-end connected queue
- util::sorted, a wrapper for keeping containers sorted

### Iterators

- util::enumerate, a Python-like helper to iterate through a container with value and index
- util::multirator, an iterator that can go through several ranges simultaneously
- util::range, a Python-like helper to create a quick range

### Helper

- util::flags
- util::non_copyable and util::non_moveable, for disallowing copying or moving on objects
- util::var, for enforcing more strict named typing
- util::ignore_unused

### Resource management

- util::guarded
- util::object
- util::scoped
- util::shared

## Usage

There are two versions of using the util library: individual headers or the whole library.
