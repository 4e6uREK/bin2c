# 4e6uREK BIN2C

<i>Fork of original bin2c suited for UNIX-like environments</i>

## Features
* Encode your data to a binary C array
```c
// Example program output

#include <stddef.h>

const size_t array_length = 4;

const char array[4] = { 0x12, 0x34, 0x56, 0x78 };
```
* Program writes output to a stdout, so you can easily redirect output to any file or even pipe to a different program like 'wl-copy'

```sh
# Redirect output to a regular file

bin2c binary_file array > main.c
```

```sh
# Pipe output to a program

bin2c binary_file array | wl-copy
```

* NOTE: Every feature except piping to a different program is cross-platform even for Windows
* NOTE: (Only for Windows) Don't target executable that have non-english letters in its path.

## Build and install for UNIX-like systems
```sh
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
make
sudo make install
```

## Build and install for Windows

1. Make sure that MSVC is installed or you can use MinGW or LLVM for build
2. Unpack source code
3. Run CMake in root source directory
4. Really recommend you to set CMAKE_BUILD_TYPE to a RELEASE
5. Build file
6. (Optionally). Add resulted executable to a $PATH environment variable
