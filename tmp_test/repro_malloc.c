#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

void *malloc(size_t size) {
  printf("CUSTOM MALLOC\n");
  void *(*real_malloc)(size_t) = dlsym(RTLD_NEXT, "malloc");
  return real_malloc(size);
}
