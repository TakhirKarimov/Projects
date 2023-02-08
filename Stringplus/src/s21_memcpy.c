#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *res1 = (char *)dest;
  const char *res2 = (char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    res1[i] = res2[i];
  }
  res1[n] = '\n';
  return dest;
}
