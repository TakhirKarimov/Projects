#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
  char *res1 = (char *)str1;
  char *res2 = (char *)str2;
  while (*res1 && *res1 == *res2 && *res2) {
    ++res1;
    ++res2;
  }

  return *res1 - *res2;
}