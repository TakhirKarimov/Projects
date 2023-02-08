#include "s21_dbinary.h"
#include "s21_decimal.h"

void set_to_inf(s21_decimal value_1, s21_decimal value_2, s21_decimal *inf) {
  if (s21_iszero(value_1) && s21_iszero(value_2))
    *inf = S21_DECIMAL_NAN;
  else
    *inf = S21_DECIMAL_INF;
  inf->bits8[15] = value_2.bits8[15] ^ value_1.bits8[15];
}

s21_decimal round_even(s21_decimal n, s21_decimal last) {
  s21_decimal min1 = s21_binsub(S21_DECIMAL_MAX, S21_DECIMAL_ONE);
  if (((n.bits8[0] & 1) && last.bits8[0] >= 5) ||
      (!(n.bits8[0] & 1) && last.bits8[0] > 5)) {
    if (s21_bincmp(n, min1) > 0) return S21_DECIMAL_INF;
    return s21_binadd(n, S21_DECIMAL_ONE);
  }
  return n;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  *result = value_2;
  value_2 = value_1;
  return 0;
}
// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//     set_to_inf(value_1, value_2, result);
//     if (s21_iszero(value_2))
//         return 3;
//     int code;
//     result->bits8[15] = value_2.bits8[15] ^ value_1.bits8[15];
//     value_2.bits8[15] = 0;
//     value_1.bits8[15] = 0;
//     while (s21_is_greater(value_2, S21_DECIMAL_ONE) &&
//            value_1.bits8[14] < 28 && value_2.bits8[14] < 28) {
//         value_1.bits8[14]++;
//         value_2.bits8[14]++;
//     }
//     while (s21_is_greater(value_2, S21_DECIMAL_ONE)) {
//         value_1 = s21_bindiv(value_1, S21_DECIMAL_TEN);
//         value_2 = s21_bindiv(value_2, S21_DECIMAL_TEN);
//         value_1.bits8[14]++;
//         value_2.bits8[14]++;
//     }
//     while (s21_is_not_equal(value_2, S21_DECIMAL_ONE)) {
//         s21_decimal G;
//         if ((code = s21_sub((s21_decimal){{2, 0}}, value_2, &G)) ||
//             (code = s21_mul(value_1, G, &value_1)) ||
//             (code = s21_mul(value_2, G, &value_2)))
//             return code;
//     }
//     result = s21_bincpy(result, &value_1);
//     result->bits8[14] = value_1.bits8[14];
//     return 0;
// }
