#include "s21_dbinary.h"
#include "s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_iszero(value_2)) return 3;
  unsigned char scale = s21_eqscale(&value_1, &value_2);
  *result = s21_binmod(value_1, value_2);
  result->bits8[14] = scale;
  result->bits8[15] = value_1.bits8[15];
  *result = s21_normalize(*result);
  return 0;
}
