

util - a collection of C++ utility classes and functions
========================================================

This library is a collection of C++ utility classes and functions. It contains 
independent self-contained headers. This means you can just copy-paste 
individual header files from this library and use them in your project without 
additional setup.

The util library contains classes and functions for

- memory management with scoped, shared and guarded RAII wrappers
- data structures like buffers and sorted containers
- network functions with endian helpers
- etc.



Licensing
---------

The util library is licensed under the MIT_ license.

.. _MIT: https://raw.githubusercontent.com/sourcechris/util/master/LICENSE.MIT

.. toctree::
   :caption: INSTALLATION
   :maxdepth: 1

   installation
   changelog

.. toctree::
   :caption: FEATURES
   :maxdepth: 1

   ressourcemanagement
   datastructures
   network

.. toctree::
   :caption: API
   :maxdepth: 2

   api/library_root

Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
