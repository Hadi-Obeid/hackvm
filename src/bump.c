#include <stddef.h>
#include "bump.h"

// Static memory bump allocator
unsigned char pool[POOL_SIZE];
size_t offset = 0;

// align to bytes (16 in case of 64 bit)
size_t align_up(size_t n, size_t a) {
  return (n + a - 1) & ~(a - 1);
}

void *bump_alloc(size_t size) {
  offset = align_up(offset, ALIGN);
  if (offset + size > POOL_SIZE)
    return NULL;
  void *p = &pool[offset];
  offset += size;
  return p;
}


void bump_reset(void) {
  offset = 0;
}

size_t bump_remaining(void) {
  return POOL_SIZE - offset;
}
