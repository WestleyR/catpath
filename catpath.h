//
// This is free and unencumbered software released into the public domain.
// 
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
// 
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
// 
// For more information, please refer to <https://unlicense.org>
//
/*

Source code: https://github.com/WestleyR/catpath

# Description

catpath.h provides a very simple, memory leak-free and easy interface for concatenate paths in C.

They are plenty of other path concatenate libraries, but they (all that I'v seen) have memory leaks,
like double malloc's and sometimes they dont have the easiest user interface.

So, I decided to create my own library, in the form of a single-file C header library, that is also
in the public domain.

catpath.h is designed for ease of use, and easy to include in your project; no other license file,
no other source files, no change to your CFLAGS, and no third-party dependencies. Just one file.


# How to use

There are two ways to use this library;

 1. Copy the catpath.h and catpath.c into your project. Then include
    and compile as normal.

 2. Copy only the catpath.h file into your project. Then define this:

    ```
    #define CATPATH_IMPLEMENTATION
    ```

    before including this header file in **one** of your C source
    files to create the implementation. Like:

    ``` your-c-file.c
    #include <stdio.h>
    #include ...
    #define CATPATH_IMPLEMENTATION
    #include "catpath.h"
    #include ...
    ```


# API

See the beginning of the header (where the function prototype start).


# CHANGELOG

### v1.1.0 - 2021-02-25 (yet to be released)
 - Added catpath.c file for users that dont want to single-file library.
 - Dont remove the slash if only appending a "/" as the file.
 - Fixed date in changelog for v1.0.1 (typ0).
 - Fixed include/defines in How to use doc section (typ0).
 - Increased the extra malloc buffer from 2 -> 4.

### v1.0.1 - 2021-01-08
 - Only add the '/' prefix if path is not empty
 - Added NULL check for file

### v1.0.0 - 2021-01-07
 - Init release.


# Contributors

This software is made possible to all the contributors.
Which include: (but not limited to)

 - WestleyR <westleyr@nym.hush.com> (author)

*/

#ifndef CATPATH_INCLUDE__H
#define CATPATH_INCLUDE__H

#include <stdlib.h> // for malloc/free
#include <string.h> // for strlen

int catpath(char** path, const char* file);
/*
catpath will take a dereference pointer, and a file/path (which must be non-null). If path
is null (which it must be when creating a new path), then it will return a new allocated
pointer. If path is non-null (like if your adding another dir/file), then it will be freed,
and re-alloced for the correct new size. It is your responsibility to `free()` the path pointer
when you are done with it. If you empty the path pointer, and call catpath again, the file
will be copied directly to the path, the prefix '/' follows from the file, and the suffix '/'
will be removed if exists.

Special notes:
 - When creating the first path, you MUST init the char pointer with NULL, see the example.
 - Make sure to call `free()` to the char pointer when you are done with it.
 - The file argument must be null-terminated.
 - When creating a new path (either from a NULL, or empty allocated pointer), the prefix
   '/' will match the file, the suffix '/' will be removed if exists.

Example:

```
  int main() {
    char* some_path = NULL; // You must init the first path with NULL!

    // Create a new allocated pointer for `some_path` with contents of: `/starts/with/slash-and-end-with-slash` (removes the suffix '/')
    catpath(&some_path, "/starts/with/slash-and-end-with-slash/");

    // Append a path to `some_path`, will automatically free/alloc a new pointer and return it
    catpath(&some_path, "/other/path");

    // some_path contents: /starts/with/slash-and-end-with-slash/other/path

    // When you are done, make sure you `free()` the path.
    free(some_path);

    return 0;
  }
```
*/

#endif // CATPATH_INCLUDE__H

//*******************
// The implementation
//*******************
#ifdef CATPATH_IMPLEMENTATION

int catpath(char** path, const char* file) {
  // file must not be null
  if (file == NULL) {
    return -1;
  }

  if (*path == NULL) {
    char* new_path = (char*) malloc(strlen(file) + 2);
    if (new_path == NULL) return -1;

    // Copy file to path
    unsigned int i = 0;
    while (*file != '\0') {
      new_path[i] = *file;
      file++;
      i++;
    }

    // If the path is not just a "/", then remove the trailing "/".
    // We dont want to remove the "/" if thats the only path we are appending.
    if (i > 1 && new_path[i-1] == '/') {
      new_path[i-1] = '\0';
    } else {
      new_path[i] = '\0';
    }

    *path = new_path;

    return 0;
  }

  // Create a new pointer, this will be the pointer to the new path
  char* new_path = (char*) malloc(strlen(*path) + strlen(file) + 4);
  if (new_path == NULL) return -1;

  strcpy(new_path, *path);
  free(*path);

  size_t path_len = strlen(new_path) - 1;

  // If the file starts with a '/', then make sure path does not start with one,
  // otherwise, add one.
  if (file[0] == '/') {
    // If theres a '/' at the suffix (which there should not be), remove it
    if (new_path[path_len] == '/') {
      new_path[path_len] = '\0';
      path_len--;
    }
  } else {
    // If theres no '/' suffix (which there should not be), then add one
    // only if path is not emtpy. If it is empty, then we should treat it
    // like a new path (only have a / prefix if file has one).
    if (new_path[path_len] != '/' && new_path[0] != '\0') {
      new_path[path_len+1] = '/';
      path_len++;
      new_path[path_len+1] = '\0';
    }
  }

  // Copy file to path
  unsigned int i = path_len + 1;
  while (*file != '\0') {
    new_path[i] = *file;
    file++;
    i++;
  }

  // Remove the trailing '/', and add the null terminator
  if (new_path[i-1] == '/') {
    new_path[i-1] = '\0';
  } else {
    new_path[i] = '\0';
  }

  // Set the return pointer
  *path = new_path;

  return 0;
}

#endif // CATPATH_IMPLEMENTATION

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0

