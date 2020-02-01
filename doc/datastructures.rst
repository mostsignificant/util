Data structures
===============

util:buffer
-----------


util::sorted_vector
-------------------

A vector of elements that are kept sorted.

This container works as a normal `std::vector 
<https://en.cppreference.com/w/cpp/container/vector>`_ with the feature that 
its elements stay sorted. The elements are sorted ascending depending on a 
given comparison function or the default std::less comparing function. There is 
no push_back function because this would interfere with the sorting. Instead 
this container features only insert functions to add elements.

