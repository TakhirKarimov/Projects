#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_dbinary.h"
#include "s21_decimal.h"

#define DSIZE sizeof(s21_decimal)

START_TEST(s21_truncate_test) {
  s21_decimal x = (s21_decimal){{92986, 0x4000000000000}};
  s21_decimal t = (s21_decimal){{9, 0}};
  ck_assert_int_eq(s21_truncate(x, &x), 0);
  fail_if(memcmp(&x, &t, DSIZE));
  x = (s21_decimal){{100000000, 0x3000000000000}};
  t = (s21_decimal){{100000, 0}};
  ck_assert_int_eq(s21_truncate(x, &x), 0);
  fail_if(memcmp(&x, &t, DSIZE));
  x = (s21_decimal){{0xB14388541B65F28, 0x1C00006582A536}};
  t = (s21_decimal){{3, 0}};
  ck_assert_int_eq(s21_truncate(x, &x), 0);  // pi(zdec)
  fail_if(memcmp(&x, &t, DSIZE));
  x = (s21_decimal){{0xEBECDE35857AED59, 0x1C000057D519AB}};
  t = (s21_decimal){{2, 0}};
  ck_assert_int_eq(s21_truncate(x, &x), 0);  // e
  fail_if(memcmp(&x, &t, DSIZE));
  // neg
  x = (s21_decimal){{92986, 0x8003000000000000}};
  t = (s21_decimal){{92, 0x8000000000000000}};
  ck_assert_int_eq(s21_truncate(x, &x), 0);
  fail_if(memcmp(&x, &t, DSIZE));
  x = (s21_decimal){{10000000, 0x8003000000000000}};
  t = (s21_decimal){{10000, 0x8000000000000000}};
  ck_assert_int_eq(s21_truncate(x, &x), 0);
  fail_if(memcmp(&x, &t, DSIZE));
  x = (s21_decimal){{0xB14388541B65F28, 0x801C00006582A536}};
  t = (s21_decimal){{3, 0x8000000000000000}};
  ck_assert_int_eq(s21_truncate(x, &x), 0);  // pi(zdec)
  fail_if(memcmp(&x, &t, DSIZE));
  x = (s21_decimal){{0xEBECDE35857AED59, 0x801C000057D519AB}};
  t = (s21_decimal){{2, 0x8000000000000000}};
  ck_assert_int_eq(s21_truncate(x, &x), 0);  // e
  fail_if(memcmp(&x, &t, DSIZE));
  // invalid
  x = S21_DECIMAL_INF;
  ck_assert_int_eq(s21_truncate(x, &x), 1);
  ck_assert_int_eq(s21_type(x), D_INF);
  x = S21_DECIMAL_INF;
  x.bits8[15] = 0x80;
  ck_assert_int_eq(s21_truncate(x, &x), 1);
  ck_assert_int_eq(s21_type(x), D_NEGINF);
  x = S21_DECIMAL_NAN;
  ck_assert_int_eq(s21_truncate(x, &x), 1);
  ck_assert_int_eq(s21_type(x), D_NAN);
}
END_TEST
START_TEST(s21_mod_test) {
  s21_decimal n = {{48, 0}};
  s21_decimal d = {{6, 0}};
  s21_decimal r = S21_DECIMAL_ZERO;
  s21_decimal q;
  // normal division
  ck_assert_int_eq(s21_mod(n, d, &q), 0);
  fail_if(memcmp(&q, &r, DSIZE));
  n = (s21_decimal){{90, 0}};
  d = (s21_decimal){{9, 0}};
  ck_assert_int_eq(s21_mod(n, d, &q), 0);
  fail_if(memcmp(&q, &r, DSIZE));
  n = (s21_decimal){{1024, 0}};
  d = (s21_decimal){{4, 0}};
  ck_assert_int_eq(s21_mod(n, d, &q), 0);
  fail_if(memcmp(&q, &r, DSIZE));
  // fractional division with diff exp
  n = (s21_decimal){{233, 0x1000000000000}};
  d = (s21_decimal){{92985, 0x4000000000000}};
  r = (s21_decimal){{4703, 0x3000000000000}};
  ck_assert_int_eq(s21_mod(n, d, &q), 0);  // 23.3%9.2985
  fail_if(memcmp(&q, &r, DSIZE));
  n = S21_DECIMAL_PI;
  d = (s21_decimal){{2, 0}};
  r = (s21_decimal){{0x8ECA33C321B65F28, 0x1C000024E30879}};
  ck_assert_int_eq(s21_mod(n, d, &q), 0);  // pi%2
  fail_if(memcmp(&q, &r, DSIZE));
  // fractional division with (almost)same exp
  n = (s21_decimal){{214, 0}};
  d = (s21_decimal){{7, 0}};
  r = (s21_decimal){{4, 0}};
  ck_assert_int_eq(s21_mod(n, d, &q), 0);  // 214%7
  fail_if(memcmp(&q, &r, DSIZE));
  n = (s21_decimal){{21, 0}};
  d = (s21_decimal){{4, 0}};
  r = (s21_decimal){{1, 0}};
  ck_assert_int_eq(s21_mod(n, d, &q), 0);  // 21%4
  fail_if(memcmp(&q, &r, DSIZE));
  n = (s21_decimal){{1, 0}};
  d = (s21_decimal){{3, 0}};
  r = (s21_decimal){{1, 0}};
  ck_assert_int_eq(s21_mod(n, d, &q), 0);  // 1%3
  fail_if(memcmp(&q, &r, DSIZE));
  n = (s21_decimal){{1, 0x1000000000000}};
  d = (s21_decimal){{3, 0}};
  r = (s21_decimal){{1, 0x1000000000000}};
  ck_assert_int_eq(s21_mod(n, d, &q), 0);  // 0.1%3
  fail_if(memcmp(&q, &r, DSIZE));
  n = (s21_decimal){{1, 0x1000000000000}};
  d = (s21_decimal){{7, 0x2000000000000}};
  r = (s21_decimal){{3, 0x2000000000000}};
  ck_assert_int_eq(s21_mod(n, d, &q), 0);  // 0.1%0.07
  fail_if(memcmp(&q, &r, DSIZE));
  // diff sign(fractional)
  n = (s21_decimal){{233, 0x8001000000000000}};
  d = (s21_decimal){{92985, 0x4000000000000}};
  r = (s21_decimal){{4703, 0x8003000000000000}};
  ;
  ck_assert_int_eq(s21_mod(n, d, &q), 0);  // -23.3%9.2985
  fail_if(memcmp(&q, &r, DSIZE));
  n = S21_DECIMAL_PI;
  d = (s21_decimal){{2, 0x8000000000000000}};
  r = (s21_decimal){{0x8ECA33C321B65F28, 0x1C000024E30879}};
  ck_assert_int_eq(s21_mod(n, d, &q), 0);  // pi%-2
  fail_if(memcmp(&q, &r, DSIZE));
}
END_TEST
START_TEST(s21_dtoi_test) {
  // pos
  s21_decimal t = S21_DECIMAL_ONE;
  int n, r = 1;
  ck_assert_int_eq(s21_from_decimal_to_int(t, &n), 0);
  ck_assert_int_eq(n, r);
  t = (s21_decimal){{0x80000000, 0x8000000000000000}};
  r = INT32_MIN;
  ck_assert_int_eq(s21_from_decimal_to_int(t, &n), 0);
  ck_assert_int_eq(n, r);
  t = S21_DECIMAL_TEN;
  r = 10;
  ck_assert_int_eq(s21_from_decimal_to_int(t, &n), 0);
  ck_assert_int_eq(n, r);
  t = S21_DECIMAL_TEN;
  r = 10;
  ck_assert_int_eq(s21_from_decimal_to_int(t, &n), 0);
  ck_assert_int_eq(n, r);
  t = (s21_decimal){{1337, 0}};
  r = 1337;
  ck_assert_int_eq(s21_from_decimal_to_int(t, &n), 0);
  ck_assert_int_eq(n, r);
  t = (s21_decimal){{1237846, 0}};
  r = 1237846;
  ck_assert_int_eq(s21_from_decimal_to_int(t, &n), 0);
  ck_assert_int_eq(n, r);
  t = (s21_decimal){{1237846, 0x8000000000000000}};
  r = -1237846;
  ck_assert_int_eq(s21_from_decimal_to_int(t, &n), 0);
  ck_assert_int_eq(n, r);
  t = (s21_decimal){{420, 0x8000000000000000}};
  r = -420;
  ck_assert_int_eq(s21_from_decimal_to_int(t, &n), 0);
  ck_assert_int_eq(n, r);
  t = S21_DECIMAL_PI;
  r = 3;
  ck_assert_int_eq(s21_from_decimal_to_int(t, &n), 0);
  ck_assert_int_eq(n, r);
  t = S21_DECIMAL_E;
  t.bits8[15] = 0x80;
  r = -2;
  ck_assert_int_eq(s21_from_decimal_to_int(t, &n), 0);
  ck_assert_int_eq(n, r);

  t = (s21_decimal){{0x80000000, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(t, &n), 1);
  t = (s21_decimal){{-1, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(t, &n), 1);
  t = S21_DECIMAL_MAX;
  ck_assert_int_eq(s21_from_decimal_to_int(t, &n), 1);
}
END_TEST
START_TEST(s21_cmp_test) {
  s21_decimal n = {{48, 0}};
  s21_decimal d = {{48, 0}};
  ck_assert_int_eq(s21_is_equal(n, d), 1);
  ck_assert_int_eq(s21_is_not_equal(n, d), 0);
  ck_assert_int_eq(s21_is_less(n, d), 0);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 1);
  ck_assert_int_eq(s21_is_greater(n, d), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 1);
  n.bits8[15] = 0x80;
  d.bits8[15] = 0x80;
  ck_assert_int_eq(s21_is_equal(n, d), 1);
  ck_assert_int_eq(s21_is_not_equal(n, d), 0);
  ck_assert_int_eq(s21_is_less(n, d), 0);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 1);
  ck_assert_int_eq(s21_is_greater(n, d), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 1);
  n.bits8[15] = 0;
  d.bits8[15] = 0x80;
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 0);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 0);
  ck_assert_int_eq(s21_is_greater(n, d), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 1);
  n.bits8[15] = 0x80;
  d.bits8[15] = 0;
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 1);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 1);
  ck_assert_int_eq(s21_is_greater(n, d), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 0);

  n = (s21_decimal){{-1, 0}};
  d = (s21_decimal){{-1, 0}};
  ck_assert_int_eq(s21_is_equal(n, d), 1);
  ck_assert_int_eq(s21_is_not_equal(n, d), 0);
  ck_assert_int_eq(s21_is_less(n, d), 0);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 1);
  ck_assert_int_eq(s21_is_greater(n, d), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 1);
  n.bits8[15] = 0x80;
  d.bits8[15] = 0x80;
  ck_assert_int_eq(s21_is_equal(n, d), 1);
  ck_assert_int_eq(s21_is_not_equal(n, d), 0);
  ck_assert_int_eq(s21_is_less(n, d), 0);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 1);
  ck_assert_int_eq(s21_is_greater(n, d), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 1);
  n.bits8[15] = 0;
  d.bits8[15] = 0x80;
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 0);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 0);
  ck_assert_int_eq(s21_is_greater(n, d), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 1);
  n.bits8[15] = 0x80;
  d.bits8[15] = 0;
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 1);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 1);
  ck_assert_int_eq(s21_is_greater(n, d), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 0);

  n = S21_DECIMAL_PI;
  d = S21_DECIMAL_E;
  n.bits8[14] = 0;
  d.bits8[14] = 0;
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 0);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 0);
  ck_assert_int_eq(s21_is_greater(n, d), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 1);
  n.bits8[15] = 0x80;
  d.bits8[15] = 0x80;
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 1);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 1);
  ck_assert_int_eq(s21_is_greater(n, d), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 0);
  n.bits8[15] = 0;
  d.bits8[15] = 0x80;
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 0);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 0);
  ck_assert_int_eq(s21_is_greater(n, d), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 1);
  n.bits8[15] = 0x80;
  d.bits8[15] = 0;
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 1);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 1);
  ck_assert_int_eq(s21_is_greater(n, d), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 0);

  n = S21_DECIMAL_PI;
  d = S21_DECIMAL_E;
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 0);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 0);
  ck_assert_int_eq(s21_is_greater(n, d), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 1);
  n.bits8[15] = 0x80;
  d.bits8[15] = 0x80;
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 1);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 1);
  ck_assert_int_eq(s21_is_greater(n, d), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 0);
  n.bits8[15] = 0;
  d.bits8[15] = 0x80;
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 0);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 0);
  ck_assert_int_eq(s21_is_greater(n, d), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 1);
  n.bits8[15] = 0x80;
  d.bits8[15] = 0;
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 1);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 1);
  ck_assert_int_eq(s21_is_greater(n, d), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 0);

  n = (s21_decimal){{127543, 0}};
  n.bits8[14] = 5;  // 1.27543
  d = (s21_decimal){{48567, 0}};
  d.bits8[14] = 2;  // 485.67
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 1);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 1);
  ck_assert_int_eq(s21_is_greater(n, d), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 0);
  n.bits8[15] = 0x80;
  d.bits8[15] = 0x80;
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 0);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 0);
  ck_assert_int_eq(s21_is_greater(n, d), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 1);
  n.bits8[15] = 0;
  d.bits8[15] = 0x80;
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 0);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 0);
  ck_assert_int_eq(s21_is_greater(n, d), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 1);
  n.bits8[15] = 0x80;
  d.bits8[15] = 0;
  ck_assert_int_eq(s21_is_equal(n, d), 0);
  ck_assert_int_eq(s21_is_not_equal(n, d), 1);
  ck_assert_int_eq(s21_is_less(n, d), 1);
  ck_assert_int_eq(s21_is_less_or_equal(n, d), 1);
  ck_assert_int_eq(s21_is_greater(n, d), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(n, d), 0);
}
END_TEST

START_TEST(s21_add_1) {
  s21_decimal src1, src2;
  int a = -1234;
  float b = 1.234;
  float res_our_dec = 0.0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1232.766;
  s21_decimal res_od;
  s21_add(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_2) {
  s21_decimal src1, src2;
  int a = -1234;
  float b = -1.234;
  float res_our_dec = 0.0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1235.234;
  s21_decimal res_od;
  s21_add(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

END_TEST
START_TEST(s21_add_4) {
  s21_decimal src1, src2;
  float a = -1234;
  float b = -221.234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1455.234;
  s21_decimal res_od;
  s21_add(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_5) {
  s21_decimal src1, src2;
  int a = -1234;
  float b = -221.234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1455.234;
  s21_decimal res_od;
  s21_add(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_7) {
  s21_decimal src1, src2;
  float a = -9403;
  float b = 0.00234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -9402.99766;
  s21_decimal res_od;
  s21_add(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_8) {
  s21_decimal src1, src2;
  int a = -9403;
  int b = 234;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -9169;
  s21_decimal res_od;
  s21_add(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_9) {
  s21_decimal src1, src2;
  float a = -940.3;
  float b = 0.000234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -940.299766;
  s21_decimal res_od;
  s21_add(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_10) {
  s21_decimal src1, src2;
  float a = -0.9403;
  float b = 0.000234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -0.940066;
  s21_decimal res_od;
  s21_add(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_11) {
  s21_decimal src1, src2;
  float a = -0.9403;
  float b = 2.0234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 1.0831;
  s21_decimal res_od;
  s21_add(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_13) {
  s21_decimal src1, src2;
  float a = -0.9403;
  float b = -112.0234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -112.9637;
  s21_decimal res_od;
  s21_add(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_14) {
  s21_decimal src1, src2;
  float a = -0.94e03;
  float b = -112.0234;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1052.0234;
  s21_decimal res_od;
  s21_add(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_15) {
  s21_decimal src1, src2;
  float a = -0.94e03;
  float b = -112.0e2;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -12140;
  s21_decimal res_od;
  s21_add(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_16) {
  s21_decimal src1, src2;
  int a = 9403;
  int b = 202;
  int res_origin = 9605;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_decimal res_od;
  s21_add(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_add_17) {
  s21_decimal src1, src2;
  src1.bits[3] = 0x300000;
  src1.bits[2] = 0;
  src1.bits[1] = 0xF;
  src1.bits[0] = 0x67E4FEEF;
  src2.bits[3] = 0x300000;
  src2.bits[2] = 0;
  src2.bits[1] = 0xFF;
  src2.bits[0] = 0x67E4FFFF;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x300000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0x10E;
  result_origin.bits[0] = 0xCFC9FEEE;
  s21_decimal result_our;
  s21_add(src1, src2, &result_our);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_add_18) {
  s21_decimal src1, src2;
  src1.bits[3] = 0x30000;
  src1.bits[2] = 0;
  src1.bits[1] = 0xFF;
  src1.bits[0] = 0x67E4F;
  src2.bits[3] = 0x60000;
  src2.bits[2] = 0;
  src2.bits[1] = 0xEA;
  src2.bits[0] = 0x67E4F;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x60000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0x3E502;
  result_origin.bits[0] = 0x1963E2E7;
  s21_decimal result_our;
  s21_add(src1, src2, &result_our);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_add_19) {
  s21_decimal src1, src2;
  src1.bits[3] = 0x30000;
  src1.bits[2] = 0;
  src1.bits[1] = 0xFFFF;
  src1.bits[0] = 0xFF837E4F;
  src2.bits[3] = 0x80070000;
  src2.bits[2] = 0;
  src2.bits[1] = 0xFFF;
  src2.bits[0] = 0xFF837E4F;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x70000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0x270FEFED;
  result_origin.bits[0] = 0x00F26FA1;
  s21_decimal result_our;
  s21_add(src1, src2, &result_our);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST
START_TEST(s21_add_20) {
  s21_decimal src1, src2;
  src2.bits8[14] = 0;
  src2.bits[2] = 0;
  src2.bits[1] = 0;
  src2.bits[0] = 0;
  s21_decimal result_origin;
  result_origin.bits[3] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0;
  s21_decimal result_our;
  ck_assert_int_eq(s21_add(S21_DECIMAL_INF, src2, &result_our), D_INF);
}
END_TEST
START_TEST(s21_round_1) {
  s21_decimal src1;
  src1.bits[0] = 0b01100011000011111111111111111111;
  src1.bits[1] = 0b01101011110001110101111000101101;
  src1.bits[2] = 0b00000000000000000000000000000101;
  src1.bits[3] = 0b10000000000010100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b01010100000010111110010000000000;
  result.bits[1] = 0b00000000000000000000000000000010;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res_od;
  s21_round(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_round_2) {
  s21_decimal src1;
  src1.bits[0] = 0b01010101001110101110101110110001;
  src1.bits[1] = 0b00001101101101001101101001011111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000100100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000000001;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res_od;
  s21_round(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_round_3) {
  s21_decimal src1;
  src1.bits[0] = 0b10010011111100000001110001010010;
  src1.bits[1] = 0b00000000000000000000000100100000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000010100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000001111100;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res_od;
  s21_round(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_round_4) {
  s21_decimal src1;
  src1.bits[0] = 0b11001101110001110111110001000000;
  src1.bits[1] = 0b00111110001001010000001001100000;
  src1.bits[2] = 0b00100000010011111100111001011110;
  src1.bits[3] = 0b10000000000001000000000000000000;
  s21_decimal result;
  result.bits[0] = 0b10100000111111100100111000000100;
  result.bits[1] = 0b00011011110011101100110011101101;
  result.bits[2] = 0b00000000000000001101001111000010;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res_od;
  s21_round(src1, &res_od);
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_round_5) {
  s21_decimal src1;
  src1.bits[0] = 0b10100000111111100100111000000100;
  src1.bits[1] = 0b00011011110011101100110011101101;
  src1.bits[2] = 0b00000000000000001101001111000010;
  src1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res_od;
  s21_round(src1, &res_od);
  s21_decimal result;
  result.bits[0] = 0b10100000111111100100111000000100;
  result.bits[1] = 0b00011011110011101100110011101101;
  result.bits[2] = 0b00000000000000001101001111000010;
  result.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_round_6) {
  s21_decimal src1;
  src1.bits[0] = 0b10010111011100111001111111111111;
  src1.bits[1] = 0b00111100000010000011000110001101;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000001110000000000000000;
  s21_decimal res_od;
  s21_round(src1, &res_od);
  s21_decimal result;
  result.bits[3] = 0;
  result.bits[2] = 0;
  result.bits[1] = 0b00000000000000000000001000010010;
  result.bits[0] = 0b00110110101101101000110001000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_round_7) {
  s21_decimal src1;
  src1.bits[0] = 0b10010111011100111001111111111111;
  src1.bits[1] = 0b00111100000010000011000110001101;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b10000000000001110000000000000000;
  s21_decimal res_od;
  s21_round(src1, &res_od);
  s21_decimal result;
  result.bits[3] = 0b10000000000000000000000000000000;
  result.bits[2] = 0;
  result.bits[1] = 0b00000000000000000000001000010010;
  result.bits[0] = 0b00110110101101101000110001000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_from_decimal_to_float_1) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 18122;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 2147680256;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -18.122);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_2) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 1812;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 2147483648;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -1812);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_3) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 0XFFFFFF;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, 16777215);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_4) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 23450987;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 2147745792;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -2345.0987);
  ck_assert_int_eq(result, 0);
}
END_TEST
START_TEST(s21_from_decimal_to_float_5) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 4294967295;
  src.bits[1] = 4294967295;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, 0xFFFFFFFFFFFFFFFF);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_sub_test) {
  int result1, result2;

  s21_decimal one, two, res1, res2;

  one = S21_DECIMAL_ZERO;
  two = S21_DECIMAL_ZERO;
  res1 = S21_DECIMAL_ZERO;
  res2 = S21_DECIMAL_ZERO;

  one.bits32[0] = 10;
  two.bits32[0] = 5;

  result1 = s21_sub(one, two, &res1);
  result2 = 0;

  res2.bits32[0] = 5;

  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
  ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);

  one = S21_DECIMAL_ZERO;
  two = S21_DECIMAL_ZERO;
  res1 = S21_DECIMAL_ZERO;
  res2 = S21_DECIMAL_ZERO;

  one.bits32[0] = 5;
  two.bits32[0] = 10;

  result1 = s21_sub(one, two, &res1);
  result2 = 0;

  res2.bits32[0] = 5;
  res2.bits8[15] = 0x80;

  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
  ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);

  one = S21_DECIMAL_ZERO;
  two = S21_DECIMAL_ZERO;
  res1 = S21_DECIMAL_ZERO;
  res2 = S21_DECIMAL_ZERO;

  one.bits32[0] = 10;
  one.bits8[15] = 0x80;
  two.bits32[0] = 5;

  result1 = s21_sub(one, two, &res1);
  result2 = 0;

  res2.bits32[0] = 15;
  res2.bits8[15] = 0x80;

  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
  ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);

  one = S21_DECIMAL_ZERO;
  two = S21_DECIMAL_ZERO;
  res1 = S21_DECIMAL_ZERO;
  res2 = S21_DECIMAL_ZERO;

  one.bits32[0] = 5;
  one.bits8[15] = 0x80;
  two.bits32[0] = 10;

  result1 = s21_sub(one, two, &res1);
  result2 = 0;

  res2.bits32[0] = 15;
  res2.bits8[15] = 0x80;

  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
  ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);

  one = S21_DECIMAL_ZERO;
  two = S21_DECIMAL_ZERO;
  res1 = S21_DECIMAL_ZERO;
  res2 = S21_DECIMAL_ZERO;

  one.bits32[0] = 5;
  two.bits32[0] = 10;
  two.bits8[15] = 0x80;

  result1 = s21_sub(one, two, &res1);
  result2 = 0;

  res2.bits32[0] = 15;

  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
  ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);

  one = S21_DECIMAL_ZERO;
  two = S21_DECIMAL_ZERO;
  res1 = S21_DECIMAL_ZERO;
  res2 = S21_DECIMAL_ZERO;

  one.bits32[0] = 5;
  two.bits32[0] = 10;
  two.bits8[15] = 0x80;

  result1 = s21_sub(one, two, &res1);
  result2 = 0;

  res2.bits32[0] = 15;

  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
  ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);

  one = S21_DECIMAL_ZERO;
  two = S21_DECIMAL_ZERO;
  res1 = S21_DECIMAL_ZERO;
  res2 = S21_DECIMAL_ZERO;

  one.bits32[0] = 10;
  one.bits8[15] = 0x80;
  two.bits32[0] = 5;
  two.bits8[15] = 0x80;

  result1 = s21_sub(one, two, &res1);
  result2 = 0;

  res2.bits32[0] = 5;
  res2.bits8[15] = 0x80;

  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
  ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);

  one = S21_DECIMAL_ZERO;
  two = S21_DECIMAL_ZERO;
  res1 = S21_DECIMAL_ZERO;
  res2 = S21_DECIMAL_ZERO;

  one.bits32[0] = 5;
  one.bits8[15] = 0x80;
  two.bits32[0] = 10;
  two.bits8[15] = 0x80;

  result1 = s21_sub(one, two, &res1);
  result2 = 0;

  res2.bits32[0] = 5;
  res2.bits8[15] = 0x80;

  ck_assert_int_eq(result1, result2);
  ck_assert_uint_eq(res1.bits32[0], res2.bits32[0]);
  ck_assert_uint_eq(res1.bits32[3], res2.bits32[3]);
}

END_TEST

START_TEST(s21_from_float_to_decimal_1) {
  s21_decimal val;

  s21_from_float_to_decimal(0.03, &val);
  ck_assert_int_eq(val.bits[0], 3);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits8[14], 2);
  ck_assert_int_eq(val.bits8[15], 0);

  s21_from_float_to_decimal(127.1234, &val);
  ck_assert_int_eq(val.bits[0], 1271234);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits8[14], 4);
  ck_assert_int_eq(val.bits8[15], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_2) {
  s21_decimal val;
  s21_from_float_to_decimal(-128.023, &val);
  ck_assert_int_eq(val.bits[0], 128023);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits8[15], 0x80);
  ck_assert_int_eq(val.bits8[14], 3);
}

END_TEST
START_TEST(s21_from_float_to_decimal_3) {
  s21_decimal val;
  s21_from_float_to_decimal(-2.1474836E+09, &val);
  ck_assert_int_eq(val.bits[0], -2147483648);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], -2147483648);
}

END_TEST
START_TEST(s21_from_float_to_decimal_4) {
  s21_decimal val;
  s21_from_float_to_decimal(22.14836E+03, &val);
  ck_assert_int_eq(val.bits[0], 2214836);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 131072);
}
END_TEST

START_TEST(s21_from_float_to_decimal_5) {
  s21_decimal val;
  s21_from_float_to_decimal(1.02E+09, &val);
  ck_assert_int_eq(val.bits[0], 1020000000);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_float_to_decimal_6) {
  s21_decimal val;
  s21_from_float_to_decimal(-333.2222, &val);
  ck_assert_int_eq(val.bits[0], 3332222);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], -2147221504);
}

END_TEST

START_TEST(s21_negate_1) {
  s21_decimal res;
  s21_decimal val;

  val.bits8[15] = 0x80;
  val.bits8[14] = 2;
  val.bits8[0] = 5;

  s21_negate(val, &res);
  ck_assert_int_eq(res.bits8[15], 0);
  ck_assert_int_eq(res.bits8[14], 2);
  ck_assert_int_eq(res.bits8[0], 5);
}

START_TEST(s21_negate_2) {
  s21_decimal res;
  s21_decimal val;

  val.bits8[15] = 0;
  val.bits8[14] = 2;
  val.bits8[0] = 5;

  s21_negate(val, &res);
  ck_assert_int_eq(res.bits8[15], 0x80);
  ck_assert_int_eq(res.bits8[14], 2);
  ck_assert_int_eq(res.bits8[0], 5);
}

END_TEST

START_TEST(s21_floor_3) {
  s21_decimal src1, krc;

  src1.bits[0] = 0b10111101001001111000010001010010;
  src1.bits[1] = 0b00000000000000000000000000011100;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000010010000000000000000;
  s21_decimal res_od;
  s21_floor(src1, &res_od);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000001111100;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_floor_5) {
  s21_decimal src1;

  src1.bits[0] = 0b01010101001110101110101110110001;
  src1.bits[1] = 0b00001101101101001101101001011111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000100100000000000000000;
  s21_decimal res_od;
  s21_floor(src1, &res_od);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000000001;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_floor_6) {
  s21_decimal src1;

  src1.bits[0] = 0b01010101001110101110101110110001;
  src1.bits[1] = 0b00001101101101001101101001011111;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000100100000000000000000;
  s21_decimal res_od;
  s21_floor(src1, &res_od);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST
START_TEST(s21_floor_7) {
  s21_decimal src1;

  src1.bits[0] = 0b10010111011100111001111111111111;
  src1.bits[1] = 0b00111100000010000011000110001101;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000001110000000000000000;
  s21_decimal result;
  s21_floor(src1, &result);
  s21_decimal result_origin;

  result_origin.bits[3] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0b00000000000000000000001000010010;
  result_origin.bits[0] = 0b00110110101101101000110000111111;
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_from_int_to_decimal_1) {
  s21_decimal val;

  s21_from_int_to_decimal(0, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  s21_from_int_to_decimal(-128, &val);
  ck_assert_int_eq(val.bits[0], 128);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], -2147483648);

  s21_from_int_to_decimal(127, &val);
  ck_assert_int_eq(val.bits[0], 127);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  s21_from_int_to_decimal(-2147483648, &val);
  ck_assert_int_eq(val.bits[0], -2147483648);
  ck_assert_int_eq(val.bits[1], -1);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], -2147483648);

  s21_from_int_to_decimal(2147483647, &val);
  ck_assert_int_eq(val.bits[0], 2147483647);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST
START_TEST(s21_mul_test_1) {
  s21_decimal src1, src2;
  int a = -32768;
  int b = 32768;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -1073741824;
  s21_decimal res_od;
  s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_mul_test_2) {
  s21_decimal src1, src2;
  int a = 9403;
  int b = 202;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = 1899406;
  s21_decimal res_od;
  s21_mul(src1, src2, &res_od);

  ck_assert_int_eq(res_od.bits64[0], res_origin);
}
END_TEST
START_TEST(s21_mul_test_3) {
  s21_decimal src1, src2;
  int a = -32768;
  int b = 2;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -65536;
  s21_decimal res_od;
  s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_mul_test_4) {
  s21_decimal src1, src2;
  int a = -32768;
  int b = 32768;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -1073741824;
  s21_decimal res_od;
  s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
}
END_TEST
START_TEST(s21_mul_test_5) {
  s21_decimal r = (s21_decimal){{0xD5661E01F1CE04F0, 0x1B00001B97E70F}};
  s21_decimal r21;
  ck_assert_int_eq(s21_mul(S21_DECIMAL_E, S21_DECIMAL_PI, &r21), 0);
  fail_if(memcmp(&r21, &r, DSIZE));
}
END_TEST
START_TEST(s21_from_int_to_decimal_2) {
  s21_decimal val;

  s21_from_int_to_decimal(0, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  s21_from_int_to_decimal(-128, &val);
  ck_assert_int_eq(val.bits[0], 128);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], -2147483648);

  s21_from_int_to_decimal(127, &val);
  ck_assert_int_eq(val.bits[0], 127);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  s21_from_int_to_decimal(-2147483648, &val);
  ck_assert_int_eq(val.bits[0], -2147483648);
  ck_assert_int_eq(val.bits[1], -1);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], -2147483648);

  s21_from_int_to_decimal(2147483647, &val);
  ck_assert_int_eq(val.bits[0], 2147483647);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

START_TEST(s21_from_int_to_decimal_3) {
  s21_decimal val;

  s21_from_int_to_decimal(INT32_MAX, &val);
  ck_assert_int_eq(val.bits[0], 2147483647);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  s21_from_int_to_decimal(INT32_MIN, &val);
  ck_assert_int_eq(val.bits[0], 2147483647);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], -2147483648);

  s21_from_int_to_decimal(0, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
}
END_TEST

Suite *test_suite(void) {
  Suite *s;
  TCase *tc1_1;

  s = suite_create("String test");
  tc1_1 = tcase_create("Core");

  tcase_add_test(tc1_1, s21_add_1);
  tcase_add_test(tc1_1, s21_add_2);
  tcase_add_test(tc1_1, s21_add_4);
  tcase_add_test(tc1_1, s21_add_5);
  tcase_add_test(tc1_1, s21_add_7);
  tcase_add_test(tc1_1, s21_add_8);
  tcase_add_test(tc1_1, s21_add_9);
  tcase_add_test(tc1_1, s21_add_10);
  tcase_add_test(tc1_1, s21_add_11);
  tcase_add_test(tc1_1, s21_add_13);
  tcase_add_test(tc1_1, s21_add_14);
  tcase_add_test(tc1_1, s21_add_15);
  tcase_add_test(tc1_1, s21_add_16);
  tcase_add_test(tc1_1, s21_add_17);
  tcase_add_test(tc1_1, s21_add_18);
  tcase_add_test(tc1_1, s21_add_19);
  tcase_add_test(tc1_1, s21_add_20);

  tcase_add_test(tc1_1, s21_from_decimal_to_float_1);
  tcase_add_test(tc1_1, s21_from_decimal_to_float_2);
  tcase_add_test(tc1_1, s21_from_decimal_to_float_3);
  tcase_add_test(tc1_1, s21_from_decimal_to_float_4);
  tcase_add_test(tc1_1, s21_from_decimal_to_float_5);

  tcase_add_test(tc1_1, s21_round_1);
  tcase_add_test(tc1_1, s21_round_2);
  tcase_add_test(tc1_1, s21_round_3);
  tcase_add_test(tc1_1, s21_round_4);
  tcase_add_test(tc1_1, s21_round_5);
  tcase_add_test(tc1_1, s21_round_6);
  tcase_add_test(tc1_1, s21_round_7);

  tcase_add_test(tc1_1, s21_truncate_test);
  tcase_add_test(tc1_1, s21_mod_test);
  tcase_add_test(tc1_1, s21_dtoi_test);
  tcase_add_test(tc1_1, s21_cmp_test);

  tcase_add_test(tc1_1, s21_sub_test);

  tcase_add_test(tc1_1, s21_from_float_to_decimal_1);
  tcase_add_test(tc1_1, s21_from_float_to_decimal_2);
  tcase_add_test(tc1_1, s21_from_float_to_decimal_3);
  tcase_add_test(tc1_1, s21_from_float_to_decimal_4);
  tcase_add_test(tc1_1, s21_from_float_to_decimal_5);
  tcase_add_test(tc1_1, s21_from_float_to_decimal_6);

  tcase_add_test(tc1_1, s21_negate_1);
  tcase_add_test(tc1_1, s21_negate_2);

  tcase_add_test(tc1_1, s21_floor_3);
  tcase_add_test(tc1_1, s21_floor_5);
  tcase_add_test(tc1_1, s21_floor_6);
  tcase_add_test(tc1_1, s21_floor_7);

  tcase_add_test(tc1_1, s21_from_int_to_decimal_1);
  tcase_add_test(tc1_1, s21_from_int_to_decimal_2);
  //    tcase_add_test(tc1_1, s21_from_int_to_decimal_3);

  tcase_add_test(tc1_1, s21_mul_test_1);
  tcase_add_test(tc1_1, s21_mul_test_2);
  tcase_add_test(tc1_1, s21_mul_test_3);
  tcase_add_test(tc1_1, s21_mul_test_4);
  tcase_add_test(tc1_1, s21_mul_test_5);

  suite_add_tcase(s, tc1_1);
  return s;
}

int main(void) {
  Suite *s = test_suite();
  SRunner *runner = srunner_create(s);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);

  int nofailed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (nofailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
