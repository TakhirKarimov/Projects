#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  value.bits8[15] = value.bits8[15] ^ 0x80;
  *result = value;
  return 0;
}
