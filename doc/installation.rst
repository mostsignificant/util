Installation
============

There are two simple ways to install and use the util library:

Individual headers
------------------

Selected functionality can be included by just copying the header file into any project. There is no additional setup
needed. For example, if you need the 
`flags <https://github.com/mostsignificant/util/blob/master/include/util/flags.hpp>`_ utility, just download the
flags.hpp file and put it in your local directory next to your source files or your include directory. 

Full project
------------

Start by cloning or downloading the project from GitHub_. Since it is a CMake project the util directory can be included
via the following CMake directive (assuming util is in a `extern` folder in the project root directory, should be
adapted to the corresponding path if necessary):

.. code-block:: cmake

    add_subdirectory(extern/util)

You also have to add it to your include directories:

.. code-block:: cmake

    target_include_directories(${TARGET}
        # ...
        util
    )

From there any util library header can be included file via the `util` path, for example the `var` class:

.. code-block:: cpp

    #include <util/var.hpp>

.. _GitHub: https://github.com/mostsignificant/util