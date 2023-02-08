#include "s21_dbinary.h"
#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  *dst = 0;
  if (s21_truncate(src, &src)) return 1;
  if (src.bits32[1] || src.bits32[2] || src.bits32[0] > 0x80000000) {
    *dst = INT32_MAX + (src.bits8[15] >> 7);
    return 1;
  }
  if (src.bits32[0] == 0x80000000 && src.bits8[15]) {
    *dst = INT32_MIN;
    return 0;
  } else if (src.bits32[0] == 0x80000000) {
    return 1;
  }
  *dst = src.bits32[0];
  if (src.bits8[15]) *dst = ~*dst + 1;
  return 0;
}
