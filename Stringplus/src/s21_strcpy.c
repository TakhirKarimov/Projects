#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  char *res1 = (char *)dest;
  const char *res2 = (char *)src;
  *res1 = *res2;
  return res1;
}