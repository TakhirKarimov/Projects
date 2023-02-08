#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  int flag_2 = 0;
  int flag_3 = 0;
  char *str1 = (char *)haystack;
  char *str2 = (char *)needle;
  int flag = 0;
  if (s21_strlen(str2) > s21_strlen(str1)) flag_3 = 1;
  if (*str2 == '\0') {
    flag_2 = 1;
  } else {
    for (; *str1 != '\0'; str1++) {
      if (*str1 == *str2) {
        int i = 0, j = 0;
        while (str1[i] && str2[j]) {
          flag = 1;
          if (str1[i] != str2[j]) {
            flag = 0;
            break;
          }
          i++;
          j++;
        }
        if (flag == 1) break;
      }
    }
  }
  char *res = s21_NULL;
  if (flag == 1) {
    res = str1;
  }
  if (flag_2 == 1) res = str1;
  if (flag_3 == 1) res = s21_NULL;
  return res;
}
