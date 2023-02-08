#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  char *res1 = (char *)dest;
  char *res2 = (char *)src;
  int size = s21_strlen(res1) + s21_strlen(res2);
  int shift = s21_strlen(res1);
  for (int i = shift; i < size; i++) {
    res1[i] = src[i - shift];
  }
  return res1;
}