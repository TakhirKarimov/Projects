#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  char *res = (char *)str;
  while (*res != c && *res != '\0' && n > 0) {
    res++;
    n--;
  }
  if (*res == '\0') {
    if (c != '\0') {
      res = s21_NULL;
    }
  } else if (n == 0) {
    res = s21_NULL;
  }
  return res;
}