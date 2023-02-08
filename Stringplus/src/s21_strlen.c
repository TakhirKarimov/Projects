#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  int count;
  for (count = 0; *(str + count); count++) {
  }
  return count;
}