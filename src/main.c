#include <stdio.h>
#include <stddef.h>
#include "parser.h"
#include "bump.h"

// Static memory pool
extern unsigned char pool[POOL_SIZE];
extern size_t offset;

int main() {
  printf("VM translator version 0.0\n");
  bump_alloc(1);
  printf("after alloc: used=%zu\n", offset);

  return 0;
}
