#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  char *res1 = (char *)str1;
  char *res2 = (char *)str2;
  int tmp;
  if (n > 0) {
    tmp = *res1 - *res2;
  } else {
    tmp = 0;
  }
  while (n > 0) {
    tmp = *res1 - *res2;
    if (tmp != 0) break;
    res1++;
    res2++;
    n--;
  }
  return tmp;
}