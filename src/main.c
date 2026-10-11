#include <stdio.h>
#include <stddef.h>
#include "parser.h"
#include "bump.h"

// Static memory pool
extern unsigned char pool[POOL_SIZE];
extern size_t offset;

int main(int argc, char** argv) {
  FILE* output;

  printf("VM translator version 0.1\n");
  if (argc == 1) {
    printf("Usage: vm [.vm files]");
  }

  output = fopen("out.asm", "w");
  for (int i = 1; i < argc; i++) {
    FILE* input_file = fopen(argv[i], "r");
    if (input_file == NULL) goto error_fopen;
    fprintf(output, "Hi!\n");
    fclose(input_file);
  }

  fclose(output);

  return 0;
error_fopen:
  printf("Failed to open file!\n");
  return 1;
}
