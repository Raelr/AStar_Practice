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

The following will use gmake as an example (however please note that other build systems are supported by premake as well). You can find a list of build system supported by premake [here](https://github.com/premake/premake-core/wiki/Using-Premake#using-premake-to-generate-project-files). Please use whatever works best for your system/configuration.

```
$ premake/premake5 gmake2
```

You should see the output as follows: 

```
Building configurations...
Running action 'gmake2'...
Generated Makefile...
Generated AStar.make...
Done (38ms).
==== Building AStar (debug) ====
Linking AStar
```

If you've seen that output then your initial build was successful! Now you should see the build files relevant to whichever system you specified show up! Now, we just need to compile the program, again this will depend on the system you use, but in this example we'll use gmake again:

```
$ make config=debug all
```

This command will now generate the executable in the appropriate location (in the bin folder). Once this is done we can now run the project itself:

```
$ ./bin/Debug/AStar
```

You should see the following output:

```
STARTING WORLD STATE:
- - - - - - - - - - 
| S |   |         | 
|   |             | 
|             |   | 
|         |   | E | 
- - - - - - - - - - 
ENDING WORLD STATE:
- - - - - - - - - - 
| S |   |         | 
| x |       x x x | 
| x     x x x | x | 
| x x x x |   | E | 
- - - - - - - - - - 
```

If you saw that, you successfully ran the project! Please feel free to play around with the code!

## License

This project uses the MIT license.
