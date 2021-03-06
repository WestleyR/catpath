# catpath.h

Single file C library to concatenate (join) file paths

## Install

There are two ways to use this library;

 1. Copy the [`catpath.h`](./catpath.h) and [`catpath.c`](./catpath.c) into your project. Then include
    and compile as normal.

 2. Copy only the catpath.h file into your project. Then define this:

    ```
    #define CATPATH_IMPLEMENTATION
    ```

    before including this header file in **one** of your C source
    files to create the implementation. Like:

    ```
    #define <stdio.h>
    #define ...
    #define CATPATH_IMPLEMENTATION
    #define "catpath.h"
    #define ...
    ```

## Example

Also see the [`test.c`](./test.c) for this example.

```c
#include <stdio.h>  // for printf
#include <stdlib.h> // for free

#define CATPATH_IMPLEMENTATION
#include "catpath.h"

int main() {
  // You must init the first path with NULL!
  char* some_path = NULL;

  // Create a new allocated pointer for `some_path` with contents of: `/starts/with/slash-and-end-with-slash` (removes the suffix '/')
  catpath(&some_path, "/starts/with/slash-and-end-with-slash/");

  // Append a path to `some_path`, will automatically free/alloc a new pointer and return it
  catpath(&some_path, "/other/path");

  printf("some_path: %s\n", some_path);
  // some_path contents: /starts/with/slash-and-end-with-slash/other/path

  // When you are done, make sure you `free()` the path.
  free(some_path);

  return 0;
}
```

## Memory leak test

Of course, there is no memory leaks. Here is the (clipped) output of
valgrind when running the compiled [`test.c`](./test.c):

```
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
  total heap usage: 3 allocs, 3 frees, 1,115 bytes allocated

All heap blocks were freed -- no leaks are possible
```

## Speed

See the [`extreme-test.c`](./extreme-test.c) for the source file. Which will run
`catpath()` 1000 times. Heres how fast it is:

```
$ gcc extreme-test.c
$ time ./a.out
some_path: (10004 chars) [...]

real    0m0.010s
user    0m0.002s
sys     0m0.003s
```

10ms is very good, and of course there is no memory leaks when running this.

