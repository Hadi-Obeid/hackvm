#pragma once
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Invariants:
// data == NULL iff len == 0
// data is not NULL terminated (not cstr)
// data can point to other buffers (view)
typedef struct {
  char *data;
  size_t len;
} String;

#define from_cstr(x) (String) {.data = x, .len = strlen(x)}

void print_str(String s);

// 0 if not equal
// 1 if equal
int str_eq(String a, String b);
int str_starts_with(String s, String prefix);
String str_take(String s, size_t n);
String str_drop(String s, size_t n);
String str_trim(String s);

String str_split(String* s, char delimiter);

String str_split_s(String*s, String* delimiter);
