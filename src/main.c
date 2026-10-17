#include <stdio.h>
#include <stddef.h>
#include "bump.h"

// Static memory pool
extern unsigned char pool[POOL_SIZE];
extern size_t offset;

#define LINE_BUF_LEN 128
static char line_buf[LINE_BUF_LEN];

int main(int argc, char** argv) {
  FILE* output;

  printf("VM translator version 0.1\n");
  if (argc == 1) {
    printf("Usage: vm [.vm files]");
  }

  output = fopen("out.asm", "w");
  if (output == NULL) goto error_fopen;
  for (int i = 1; i < argc; i++) {
    FILE* input_file = fopen(argv[i], "r");
    if (input_file == NULL) goto error_fopen;

    while (fgets(line_buf, LINE_BUF_LEN, input_file)) {
      printf("%s", line_buf);
    }
    fclose(input_file);
  }

  fclose(output);

  return 0;
error_fopen:
  printf("Failed to open file!\n");
  return 1;
}
