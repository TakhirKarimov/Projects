#include "s21_decimal.h"
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  dst->bits64[0] = dst->bits64[1] = 0;

  if (src < 0) dst->bits8[15] = 0x80;
  dst->bits64[0] = src < 0 ? src * -1 : src;

  return 0;
}
