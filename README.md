treemap
=======

A simple, minimalistic tree map in C based on a Red-Black tree algoritm found somewhere.
Credits should be given to the guys that wrote the original PDF with the algorithm, but several years have passed and I cannot remember who they were.

This should be optimized though, MapIterator is pretty inefficient; but I just needed this to work and I never pretended it could be a replacement for better engineered implementations.

The whole code is LGPL-v3 covered and pretty much undocumented.

This is C11 compliant (should work with a C99 compiler).
Makefile is pretty much barebone and expects the presence of clang, binutils and jemalloc.
