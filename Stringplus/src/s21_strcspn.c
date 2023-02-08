#include "s21_string.h"

int s21_strcspn(const char *str1, const char *str2) {
  int res1 = s21_strlen(str1);
  int res2 = s21_strlen(str2);
  int flag = 0;
  int i;
  for (i = 0; i < res1; i++) {
    for (int j = 0; j < res2; j++)
      if (str1[i] == str2[j]) {
        flag = 1;
        break;
      }
    if (flag) break;
  }
  return i;
}
