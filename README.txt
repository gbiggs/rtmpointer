rtmpointer
==========

Pointer-passing transport for OpenRTM-aist.

This transport allows multiple components to use a single memory
location to share data. The data is accessed via a pointer provided to
the transport when a port is created. There is no distinction between
readers and writers; the port is considered read/write.

This transport is designed exclusively for use in composite components
where all components are executing in the same component manager within
a single address space and the composites are executing in series.
Parallel execution will lead to race conditions. Use with components
executing in separate memory spaces will lead to memory access errors.

This software is developed at the National Institute of Advanced
Industrial Science and Technology. Approval number H23PRO-1302. This
software is licensed under the Lesser General Public License. See
COPYING.LESSER.

