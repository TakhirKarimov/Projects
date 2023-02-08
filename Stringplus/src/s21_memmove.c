#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *res1 = (char *)dest;
  char *res2 = (char *)src;
  if (s21_strlen(res1) < n) {
    n = s21_strlen(res1);
    *res1 = *res2;
  }
  for (s21_size_t i = 0; i < n; i++) {
    res1[i] = res2[i];
  }
  res1[n] = '\0';
  return dest;
}
