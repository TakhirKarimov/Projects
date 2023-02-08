#include "s21_dbinary.h"
#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  uint32_t sign_1 = value_1.bits8[15] == 0x80,
           sign_2 = value_2.bits8[15] == 0x80;
  int32_t type_1 = s21_type(value_1), type_2 = s21_type(value_2);
  if (type_1 == D_NORMAL && type_2 == D_NORMAL) {
    result->bits8[14] = s21_eqscale(&value_1, &value_2);
    if (!sign_1 && !sign_2) {
      if (s21_is_greater_or_equal(value_1, value_2)) {
        *result = s21_binsub(value_1, value_2);
      } else {
        *result = s21_binsub(value_2, value_1);
        result->bits8[15] = 0x80;
      }
    } else if (sign_1 && sign_2) {
      if (s21_is_greater_or_equal(value_1, value_2)) {
        *result = s21_binsub(value_2, value_1);
        result->bits8[15] = 0x80;
      } else {
        *result = s21_binsub(value_1, value_2);
        result->bits8[15] = 0x80;
      }
    } else if (sign_1 && !sign_2) {
      *result = s21_binadd(value_1, value_2);
      result->bits8[15] = 0x80;
    } else {
      *result = s21_binadd(value_1, value_2);
    }
  } else if (type_1 == D_INF || type_2 == D_INF) {
    error = 1;
  } else if (type_1 == D_NEGINF || type_2 == D_NEGINF) {
    error = 2;
  }
  return error;
}
