#include "s21_dbinary.h"
#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int code = s21_truncate(value, result);
  if (value.bits8[15]) *result = s21_binadd(*result, S21_DECIMAL_ONE);
  return code;
}
