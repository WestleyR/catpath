# catpath.h

Single file C library to concatenate (join) file paths

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

Of course, there is no memory leaks. Here is the (cliped) output of
valgrind when running the compiled `test.c`:

```
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
  total heap usage: 3 allocs, 3 frees, 1,115 bytes allocated

All heap blocks were freed -- no leaks are possible
```

