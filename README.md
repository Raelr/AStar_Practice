# AStar_Practice

A small (and highly specialised) A* implementation written in C++. The implementation tries to use procedural programming as the primary paradigm for development. This implementation tries to not use any classes for design but rather uses structs and global methods.

The implementation uses 2D arrays (as well as flattened 2D arrays) for its indexing and storage. The nodes themselves are sorted via the use of a nodeheap (the implementation was inspired by Sebastian Lague's [NodeHeap implementation](https://www.youtube.com/watch?v=3Dw5d7PlcTM&t=906s)). Vectors are used within the NodeHeap, so this isn't a pure non-STL using implementation (might be fixed later on). 

## Setup 

This can be run using a number of methods:

1. Use Premake and your build system to run the program (This uses gmake)
2. Run the provided bash (and bat) scripts.
3. Build the program manually using your C++ compiler.

This setup guide will focus on options 1 and 2. 

### Premake - Manual (MacOS and Linux)

Run the following command:

```
premake/premake5 gmake2
```

You should see the output as follows: 


