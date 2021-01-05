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

# Description

_todo_

# How to use

Define this:
  #define CATPATH_IMPLEMENTATION

before including this header file in **one** of your C source
files to create the implementation.


# API

See the begining of the header (where the function prototype start).


# CHANGELOG

### v1.0.0 - 2021-01-04 (yet to be released)
 - Init release.


# Contributors

This software is made possible to all the contributors.
Which include: (but not limited to)

 - WestleyR <westleyr@nym.hush.com> (author)

*/

#ifndef CATPATH_INCLUDE__H
#define CATPATH_INCLUDE__H

#include <stdlib.h>
#include <string.h>

// TODO: debugging
#include <stdio.h>

int catpath(char** path, const char* file);

#endif // CATPATH_INCLUDE__H

//*******************
// The implementation
//*******************
#ifdef CATPATH_IMPLEMENTATION

int catpath(char** path, const char* file) {
  if (*path == NULL) {
    char* ptr = (char*) malloc(strlen(file) + 2);
    if (ptr == NULL) return -1;

    // Copy file to path
    unsigned int i = 0;
    while (*file != '\0') {
      ptr[i] = *file;
      file++;
      i++;
    }
    ptr[i] = '\0';

    *path = ptr;

    return 0;
  }

  // Create a new pointer, this will be the pointer to the new path
  char* new_path = (char*) malloc(strlen(*path) + strlen(file) + 2);
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
    if (new_path[path_len+1] != '/') {
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

  if (new_path[i-1] == '/') {
    new_path[i-1] = '\0';
  }
  new_path[i] = '\0';

  *path = new_path;

  return 0;
}

#endif // CATPATH_IMPLEMENTATION

// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0

