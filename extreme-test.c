#include <stdio.h>  // for printf
#include <stdlib.h> // for free
#include <string.h> // for strlen

#define CATPATH_IMPLEMENTATION
#include "catpath.h"

int main() {
  char* some_path = NULL;

  catpath(&some_path, "base");

  // Extreme test case, and no memory leaks! (also very fast; <10ms to run this program)
  for (int i = 0; i < 1000; i++) {
    catpath(&some_path, "some/path");
  }

  printf("some_path: (%ld chars) %s\n", strlen(some_path), some_path);

  free(some_path);

  return 0;
}
