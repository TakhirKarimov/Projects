#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *res = (char *)str;
  while (*res != '\0' && *res != c) {
    res++;
  }
  if (*res == '\0') res = s21_NULL;
  return res;
}
