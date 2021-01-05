
#include <stdio.h>
#include <stdlib.h>

#define CATPATH_IMPLEMENTATION
#include "catpath.h"

int test1() {
  printf("%s()\n", __func__);

  char* path = NULL;

  catpath(&path, "/start-and-end-with-slashes/");
  printf("PATH: %s\n", path);

  catpath(&path, "/plus/path/with/slashes/");
  printf("PATH: %s\n", path);

  free(path);

  return 0;
}

int test2() {
  printf("\n%s()\n", __func__);

  char* new_path = NULL;

  catpath(&new_path, "no-start-slash");
  printf("PATH: %s\n", new_path);

  catpath(&new_path, "no-leading-slash");
  printf("PATH: %s\n", new_path);

  free(new_path);

  return 0;
}

int test3() {
  printf("\n%s()\n", __func__);

  char* path = NULL;

  catpath(&path, "/starts-with-slash");
  printf("PATH: %s\n", path);

  catpath(&path, "/with/more/slashes/");
  printf("PATH: %s\n", path);

  free(path);

  return 0;
}


int main(int argc, char** argv) {
  test1();
  test2();
  test3();

  return(0);
}


// vim: tabstop=2 shiftwidth=2 expandtab autoindent softtabstop=0

