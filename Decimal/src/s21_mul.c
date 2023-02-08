#include "s21_dbinary.h"
#include "s21_decimal.h"

s21_decimal cut(s21_decimal value) {
  value = s21_bindiv(value, S21_DECIMAL_TEN);
  s21_decimal last = s21_binmod(value, S21_DECIMAL_TEN);
  if (last.bits8[0] >= 5) value = s21_binadd(value, S21_DECIMAL_ONE);
  value.bits8[14]--;
  return value;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  while (value_1.bits8[14] + value_2.bits8[14] > 28) {
    value_2 = cut(value_2);
    if (!((value_1.bits8[14] + value_2.bits8[14]) % 2)) value_1 = cut(value_1);
  }
  if (s21_bincmp(s21_bindiv(S21_DECIMAL_MAX, value_2), value_1) < 0) {
    value_1 = s21_bindiv(value_1, S21_DECIMAL_TEN);
    result->bits8[14]--;
  }

  *result = s21_binmul(value_1, value_2);
  result->bits8[14] = value_1.bits8[14] + value_2.bits8[14];
  *result = s21_normalize(*result);
  return 0;
}
