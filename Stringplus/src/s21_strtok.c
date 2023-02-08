#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *res;

  if (str) {
    for (res = str; s21_strchr(delim, *res); ++res)
      ;
  }
  if (*res == '\0') return s21_NULL;

  str = res;
  while (*res && !s21_strchr(delim, *res)) ++res;
  while (*res && s21_strchr(delim, *res)) *res++ = '\0';

  return str;
}