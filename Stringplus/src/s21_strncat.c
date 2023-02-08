#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *res1 = (char *)dest;
  int size = s21_strlen(res1) + n;
  int shift = s21_strlen(res1);
  for (int i = shift; i < size; i++) {
    res1[i] = src[i - shift];
  }
  return res1;
}