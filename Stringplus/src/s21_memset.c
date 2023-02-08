#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  char *res = str;
  s21_size_t i = 0;
  if (s21_strlen(res) >= n) {
    for (i = 0; i < n; i++) {
      res[i] = c;
    }
  }
  return res;
}