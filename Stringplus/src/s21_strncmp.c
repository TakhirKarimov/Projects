#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  const char *res = str1 + n;
  int error = 0;
  for (; error == 0 && str1 != res && (*str1 || *str2);
       error = *(str1++) - *(str2++))
    ;
  return error;
}