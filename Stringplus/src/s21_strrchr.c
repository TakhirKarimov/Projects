#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *res = s21_NULL;
  int flag = 0;
  char *tmp = (char *)str;
  int res_pos = 0;
  int pos = 0;
  for (; *tmp != '\0'; tmp++, pos++) {
    if (*tmp == c) {
      res_pos = pos;
      flag = 1;
    }
  }
  if (flag) res = (char *)&str[res_pos];
  return res;
}