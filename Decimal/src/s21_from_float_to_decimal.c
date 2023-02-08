#include <math.h>

#include "s21_decimal.h"

typedef union {
  float f;
  struct {
    uint32_t mantisa : 23;
    uint32_t exponent : 8;
    uint32_t sign : 1;
  } parts;
} float_cast;

void s21_float_convert(s21_decimal *val, uint32_t mant, int32_t exp) {
  val->bits32[exp / 32] |= 1 << exp % 32;
  for (int i = exp - 1, j = 22; j; i--, j--) {
    if ((mant & (1 << j))) val->bits32[i / 32] |= 1 << i % 32;
  }
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int32_t error = 1;
  *dst = S21_DECIMAL_ZERO;
  float_cast fl;

  fl.f = src;
  int32_t exp = fl.parts.exponent - 127, sign = fl.parts.sign;
  int32_t scale = 0;
  src = fabsf(src);

  for (; scale < 28 && (int32_t)src / (int32_t)pow(2, 21) == 0;
       src *= 10, scale++) {
  }

  src = roundf(src);

  if (src && exp < 96 && scale <= 28 && exp > -94) {
    for (; fmod(src, 10) == 0 && scale > 0; scale--, src /= 10) {
    }
    fl.f = src;
    exp = fl.parts.exponent - 127;
    uint32_t mant = fl.parts.mantisa;
    dst->bits8[15] = !sign ? 0 : 0x80;
    s21_float_convert(dst, mant, exp);
    dst->bits8[14] = scale;

    error = 0;
  }
  return error;
}
