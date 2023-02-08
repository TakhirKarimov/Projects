#include "s21_dbinary.h"
#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  *result = value;
  if (s21_type(value)) return 1;
  s21_decimal tenpow = s21_pow10(result->bits8[14]);
  *result = s21_bindiv(*result, tenpow);
  result->bits8[14] = 0;
  return 0;
}
