#include <stdio.h>

#include "s21_dbinary.h"
#include "s21_dconst.h"
#include "s21_decimal.h"
#define MAX 4294967295

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  uint32_t sign_1 = value_1.bits8[15], sign_2 = value_2.bits8[15];
  int32_t type_1 = s21_type(value_1), type_2 = s21_type(value_2);
  if ((type_1 == D_NORMAL && type_2 == D_NORMAL) ||
      (type_1 == D_NAN || type_2 == D_NAN)) {
    result->bits8[14] = s21_eqscale(&value_1, &value_2);
    if (!sign_1 && !sign_2) {
      *result = s21_binadd(value_1, value_2);
    } else if (sign_1 && sign_2) {
      *result = s21_binadd(value_1, value_2);
      result->bits8[15] = 0x80;
    } else if (sign_1 && !sign_2) {
      s21_negate(value_1, &value_1);
      if (s21_is_greater_or_equal(value_1, value_2)) {
        s21_negate(value_1, &value_1);
        *result = s21_binsub(value_1, value_2);
        result->bits8[15] = 0x80;
      } else {
        s21_negate(value_1, &value_1);
        *result = s21_binsub(value_2, value_1);
      }
    } else {
      s21_negate(value_2, &value_2);
      if (s21_is_greater_or_equal(value_1, value_2)) {
        s21_negate(value_2, &value_2);
        *result = s21_binsub(value_1, value_2);
      } else {
        s21_negate(value_2, &value_2);
        *result = s21_binsub(value_2, value_1);
        result->bits8[15] = 0x80;
      }
    }
  } else if (type_1 == D_INF || type_2 == D_INF) {
    error = 1;
  } else if (type_1 == D_NEGINF || type_2 == D_NEGINF) {
    error = 2;
  }
  return error;
}
