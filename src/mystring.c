#include <stdio.h>
#include "mystring.h"

void print_str(String s) {
  for (size_t i = 0; i < s.len; i++) {
    putchar(s.data[i]);
  }
}

// 0 if not equal
// 1 if equal
int str_eq(String a, String b) {
  if (a.len != b.len) return 0;
  for (size_t i = 0; i < a.len; ++i) {
    if (a.data[i] != b.data[i]) return 0;
  }
  return 1;
}

int str_starts_with(String s, String prefix) {
  if (prefix.len > s.len) return 0;
  for (size_t i = 0; i < prefix.len; ++i) {
    if (s.data[i] != prefix.data[i]) return 0;
  }
  return 1;
}

String str_take(String s, size_t n) {
  if (n > s.len) n = s.len;
  return (String) {
    .data = s.data,
    .len = n
  };
}
String str_drop(String s, size_t n) {
  if (n > s.len) n = s.len;
  return (String) {
    .data = s.data + n,
    .len = s.len - n
  };
}

String str_trim(String s) {
  while (s.len > 0 && isspace((unsigned char) s.data[0])) {
    s = str_drop(s, 1);
  }
  while (s.len > 0 && isspace((unsigned char) s.data[s.len-1])) {
    s = str_take(s, s.len - 1);
  }
  return s;
}


String str_split(String* s, char delimiter) {
  size_t i = 0;
  while ( i < s->len && s->data[i] != delimiter)
    ++i;

  String result = str_take(*s, i);
  if (i < s->len) {
    *s = str_drop(*s, i + 1);
  } else {
    *s = str_drop(*s, i);
  }
  return result;
}

String str_split_s(String*s, String* delimiter) {

  if (delimiter->len == 0) {
    String r = str_take(*s, 0);
    return r;
  }

  size_t i = 0;
  for (; i + delimiter->len <= s->len; ++i) {
    if (memcmp(s->data+i, delimiter->data, delimiter->len) == 0)
      break;
  }
  String result = str_take(*s, i);
  size_t skip = (i + delimiter->len <= s->len) ? i + delimiter->len : i;
  *s = str_drop(*s, skip);
  return result;
}
