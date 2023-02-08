#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  int pos = 0, flag = 0;
  char *res = s21_NULL;
  char *tmp = (char *)str1;
  s21_size_t lstr1 = s21_strlen(str1);
  s21_size_t lstr2 = s21_strlen(str2);
  for (; *tmp != '\0'; tmp++) {
    for (s21_size_t j = 0; j < lstr2; j++) {
      for (s21_size_t i = 0; i < lstr1; i++) {
        if (str1[i] == str2[j]) {
          pos = i;
          flag = 1;
          break;
        }
      }
      if (flag) {
        break;
      }
    }
    if (flag) {
      break;
    }
  }
  if (flag) res = (char *)&str1[pos];
  return res;
}
