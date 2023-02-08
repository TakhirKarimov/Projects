#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  int len = 0;
  int flag = 0;
  char *res1 = (char *)str1;
  for (; *res1 != '\0'; res1++) {
    if (flag == 2) {
      break;
    }
    for (int j = 0; str2[j] != '\0'; j++) {
      if (*res1 == str2[j]) {
        flag = 1;
        break;
      } else if (flag == 1 && str2[j + 1] == '\0') {
        flag = 2;
        break;
      }
    }
    if (flag == 1) len++;
  }
  return len;
}