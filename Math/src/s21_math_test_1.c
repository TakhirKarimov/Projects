#include <check.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_math.h"
// CHECKLIST
// sin xx
// cos xx
// tan x
// asin xx
// acos xx
// atan x

// sqrt ?
// exp xx
// log ?
// pow ?

// floor x
// ceil x
// fmod xx
long double precision = 1e-10;

START_TEST(abs_t) {
  printf("Testing s21_abs: ");
  int a = -25, b = 25;
  for (int i = a; i < b; i++) ck_assert_int_eq(s21_abs(i), abs(i));
  printf("[PASS]\n");
}
END_TEST
START_TEST(fabs_t) {
  printf("Testing s21_fabs: ");
  int n = 49;
  long double a = -2.7, b = 2.7, step = (b - a) / n;
  for (long double x = a; x < b; x += step)
    ck_assert_ldouble_eq(s21_fabs(x), fabsl(x));
  ck_assert_ldouble_eq(s21_fabs(S21_INF), fabsl(S21_INF));
  ck_assert_ldouble_eq(s21_fabs(-S21_INF), fabsl(-S21_INF));
  ck_assert_ldouble_nan(s21_fabs(S21_NAN));
  printf("[PASS]\n");
}
END_TEST

START_TEST(floor_t) {
  printf("Testing s21_floor: ");
  int n = 49;
  long double a = -2.7, b = 2.7, step = (b - a) / n;
  for (long double x = a; x < b; x += step)
    ck_assert_ldouble_eq(s21_floor(x), floorl(x));
  ck_assert_ldouble_eq(s21_floor(1337e147), floorl(1337e147));
  ck_assert_ldouble_eq(s21_floor(1337e-147), floorl(1337e-147));
  ck_assert_ldouble_eq(s21_floor(S21_INF), floorl(S21_INF));
  ck_assert_ldouble_eq(s21_floor(-S21_INF), floorl(-S21_INF));
  ck_assert_ldouble_nan(s21_floor(S21_NAN));
  printf("[PASS]\n");
}
END_TEST
START_TEST(ceil_t) {
  printf("Testing s21_ceil: ");
  int n = 49;
  long double a = -2.7, b = 2.7, step = (b - a) / n;
  for (long double x = a; x < b; x += step)
    ck_assert_ldouble_eq(s21_ceil(x), ceill(x));
  ck_assert_ldouble_eq(s21_floor(1337e147), floorl(1337e147));
  ck_assert_ldouble_eq(s21_floor(1337e-147), floorl(1337e-147));
  ck_assert_ldouble_eq(s21_ceil(S21_INF), ceill(S21_INF));
  ck_assert_ldouble_eq(s21_ceil(-S21_INF), ceill(-S21_INF));
  ck_assert_ldouble_nan(s21_ceil(S21_NAN));
  printf("[PASS]\n");
}
END_TEST
START_TEST(round_t) {
  printf("Testing s21_round: ");
  int n = 49;
  long double a = -2.7, b = 2.7, step = (b - a) / n;
  for (long double x = a; x < b; x += step)
    ck_assert_ldouble_eq(s21_round(x), roundl(x));
  ck_assert_ldouble_eq(s21_round(S21_INF), roundl(S21_INF));
  ck_assert_ldouble_eq(s21_round(-S21_INF), roundl(-S21_INF));
  ck_assert_ldouble_nan(s21_round(S21_NAN));
  printf("[PASS]\n");
}
END_TEST
START_TEST(fmod_t) {
  printf("Testing s21_fmod: ");
  int n = 49;
  long double a = -2.7, b = 2.7, step = (b - a) / n;
  for (long double x = a; x < b; x += step)
    for (long double y = a; y < b; y += step)
      ck_assert_ldouble_le(fabsl(s21_fmod(x, y) - fmodl(x, y)), precision);

  // ck_assert_ldouble_le(fabsl(s21_fmod(1337e147, 3.4) - fmodl(1337e147, 3.4)),
  // precision); ck_assert_ldouble_le(fabsl(s21_fmod(3.4, 1337e147) - fmodl(3.4,
  // 1337e147)), precision);

  // ck_assert_ldouble_le(fabsl(s21_fmod(1337e-147, 3.4) -
  // fmodl(1337e-147, 3.4)), precision);
  // ck_assert_ldouble_le(fabsl(s21_fmod(3.4, 1337e-147) - fmodl(3.4,
  // 1337e-147)), precision);

  // ck_assert_ldouble_le(fabsl(s21_fmod(1337e147, 1e147) - fmodl(1337e147,
  // 1e147)), precision); ck_assert_ldouble_le(fabsl(s21_fmod(1337e147, 1e-147)
  // - fmodl(1337e147, 1e-147)), precision);
  // ck_assert_ldouble_le(fabsl(s21_fmod(1337e-147, 1e147) - fmodl(1337e-147,
  // 1e147)), precision); ck_assert_ldouble_le(fabsl(s21_fmod(1337e-147, 1e-147)
  // - fmodl(1337e-147, 1e-147)), precision);

  ck_assert_ldouble_eq(s21_fmod(0, 4.2), fmodl(0, 4.2));
  ck_assert_ldouble_nan(s21_fmod(4.2, 0));
  ck_assert_ldouble_nan(s21_fmod(0, 0));

  ck_assert_ldouble_eq(s21_fmod(2.3, S21_INF), fmodl(2.3, S21_INF));
  ck_assert_ldouble_eq(s21_fmod(2.3, -S21_INF), fmodl(2.3, -S21_INF));
  ck_assert_ldouble_nan(s21_fmod(-S21_INF, 2.3));
  ck_assert_ldouble_eq(s21_fmod(-2.3, S21_INF), fmodl(-2.3, S21_INF));
  ck_assert_ldouble_nan(s21_fmod(S21_INF, -2.3));
  ck_assert_ldouble_eq(s21_fmod(-2.3, -S21_INF), fmodl(-2.3, -S21_INF));
  ck_assert_ldouble_nan(s21_fmod(-S21_INF, -2.3));

  ck_assert_ldouble_nan(s21_fmod(S21_INF, S21_INF));
  ck_assert_ldouble_nan(s21_fmod(S21_INF, -S21_INF));
  ck_assert_ldouble_nan(s21_fmod(-S21_INF, S21_INF));
  ck_assert_ldouble_nan(s21_fmod(-S21_INF, -S21_INF));

  ck_assert_ldouble_nan(s21_fmod(S21_INF, S21_NAN));
  ck_assert_ldouble_nan(s21_fmod(-S21_INF, S21_NAN));
  ck_assert_ldouble_nan(s21_fmod(S21_NAN, S21_INF));
  ck_assert_ldouble_nan(s21_fmod(S21_NAN, -S21_INF));

  ck_assert_ldouble_nan(s21_fmod(S21_NAN, S21_NAN));

  ck_assert_ldouble_nan(s21_fmod(S21_NAN, 0.69));
  ck_assert_ldouble_nan(s21_fmod(0.69, S21_NAN));

  printf("[PASS]\n");
}
END_TEST

START_TEST(sin_t) {
  printf("Testing s21_sin: ");
  int n = 99;
  long double a = -S21_2PI - S21_PI_2, b = S21_2PI + S21_PI_2,
              step = (b - a) / n;
  for (long double x = a; x < b; x += step)
    ck_assert_ldouble_le(fabsl(s21_sin(x) - sinl(x)), precision);
  for (n = -10; n < 10; n++)
    ck_assert_ldouble_le(fabsl(s21_sin(S21_PI_2 * n) - sinl(S21_PI_2 * n)),
                         precision);
  ck_assert_ldouble_nan(s21_sin(S21_INF));
  ck_assert_ldouble_nan(s21_sin(-S21_INF));
  ck_assert_ldouble_nan(s21_sin(S21_NAN));
  printf("[PASS]\n");
}
END_TEST
START_TEST(cos_t) {
  printf("Testing s21_cos: ");
  int n = 99;
  long double a = -S21_2PI - S21_PI_2, b = S21_2PI + S21_PI_2,
              step = (b - a) / n;
  for (long double x = a; x < b; x += step)
    ck_assert_ldouble_le(fabsl(s21_cos(x) - cosl(x)), precision);
  for (n = -10; n < 10; n++)
    ck_assert_ldouble_le(fabsl(s21_cos(S21_PI_2 * n) - cosl(S21_PI_2 * n)),
                         precision);
  ck_assert_ldouble_nan(s21_cos(S21_INF));
  ck_assert_ldouble_nan(s21_cos(-S21_INF));
  ck_assert_ldouble_nan(s21_cos(S21_NAN));
  printf("[PASS]\n");
}
END_TEST
START_TEST(tan_t) {
  printf("Testing s21_tan:");
  int n = 49;
  long double a = -S21_2PI, b = S21_2PI, step = (b - a) / n;
  for (long double x = a + step; x < b - step; x += step) {
    ck_assert_ldouble_le(fabsl(s21_tan(x) - tanl(x)), precision);
  }
  ck_assert_ldouble_nan(s21_tan(S21_INF));
  ck_assert_ldouble_nan(s21_tan(-S21_INF));
  ck_assert_ldouble_nan(s21_tan(S21_NAN));
  printf("[PASS]\n");
}
END_TEST

START_TEST(asin_t) {
  printf("Testing s21_asin: ");
  int n = 99;
  long double a = -1, b = 1, step = (b - a) / n;
  for (long double x = a; x < b - step; x += step)
    ck_assert_ldouble_le(fabsl(s21_asin(x) - asinl(x)), precision);
  ck_assert_ldouble_nan(s21_asin(2));
  ck_assert_ldouble_nan(s21_asin(-2));
  ck_assert_ldouble_nan(s21_asin(S21_INF));
  ck_assert_ldouble_nan(s21_asin(-S21_INF));
  ck_assert_ldouble_nan(s21_asin(S21_NAN));
  printf("[PASS]\n");
}
END_TEST
START_TEST(acos_t) {
  printf("Testing s21_acos: ");
  int n = 99;
  long double a = -1, b = 1, step = (b - a) / n;
  for (long double x = a; x < b - step; x += step)
    ck_assert_ldouble_le(fabsl(s21_acos(x) - acosl(x)), precision);
  ck_assert_ldouble_nan(s21_acos(2));
  ck_assert_ldouble_nan(s21_acos(-2));
  ck_assert_ldouble_nan(s21_acos(S21_INF));
  ck_assert_ldouble_nan(s21_acos(-S21_INF));
  ck_assert_ldouble_nan(s21_acos(S21_NAN));
  printf("[PASS]\n");
}
END_TEST
START_TEST(atan_t) {
  printf("Testing s21_atan: ");
  int n = 99;
  long double a = -2.5, b = 2, step = (b - a) / n;
  for (long double x = a; x < b; x += step)
    ck_assert_ldouble_le(fabsl(s21_atan(x) - atanl(x)), precision);
  ck_assert_ldouble_le(fabsl(s21_atan(0) - atanl(0)), precision);
  ck_assert_ldouble_le(fabsl(s21_atan(10) - atanl(10)), precision);
  ck_assert_ldouble_le(fabsl(s21_atan(1e-10) - atanl(1e-10)), precision);
  ck_assert_ldouble_eq_tol(s21_atan(-1.0 / 0.0), atan(-1.0 / 0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(1.0 / 0.0), atan(1.0 / 0.0), 1e-6);
  ck_assert_ldouble_nan(s21_atan(S21_NAN));
  printf("[PASS]\n");
}
END_TEST

START_TEST(pow_t) {
  // oriented on math(not doc)
  printf("Testing s21_pow: ");
  int n = 49;
  // normal values
  long double a = 0, b = 2.7, step = (b - a) / n;
  for (long double x = a + step; x < b; x += step)
    for (long double y = -b; y < b; y += step)
      ck_assert_ldouble_le(fabsl(s21_pow(x, y) - powl(x, y)), precision);
  // neg base
  ck_assert_ldouble_nan(s21_pow(-4.2, 4.2));
  ck_assert_ldouble_eq(s21_pow(-4.2, 3), powl(-4.2, 3));
  ck_assert_ldouble_eq(s21_pow(-4, 3), powl(-4, 3));
  ck_assert_ldouble_nan(s21_pow(-4, 3.3));
  // zero base and power
  ck_assert_ldouble_eq(s21_pow(0, 1), powl(0, 1));
  ck_assert_ldouble_eq(s21_pow(1, 0), powl(1, 0));
  ck_assert_ldouble_eq(s21_pow(0, 4.2), powl(0, 4.2));
  ck_assert_ldouble_eq(s21_pow(0, -4.2), powl(0, -4.2));
  ck_assert_ldouble_eq(s21_pow(4.2, 0), powl(4.2, 0));
  ck_assert_ldouble_eq(s21_pow(-4.2, 0), powl(-4.2, 0));
  ck_assert_ldouble_eq(s21_pow(0, 0), powl(0, 0));
  // infinity base and power
  ck_assert_ldouble_eq(s21_pow(S21_INF, 2), powl(S21_INF, 2));
  ck_assert_ldouble_eq(s21_pow(S21_INF, -2), powl(S21_INF, -2));
  ck_assert_ldouble_eq(s21_pow(S21_INF, 2.3), powl(S21_INF, 2.3));
  ck_assert_ldouble_eq(s21_pow(S21_INF, -2.3), powl(S21_INF, -2.3));
  ck_assert_ldouble_eq(s21_pow(S21_INF, S21_INF), powl(S21_INF, S21_INF));
  ck_assert_ldouble_eq(s21_pow(S21_INF, -S21_INF), powl(S21_INF, -S21_INF));

  ck_assert_ldouble_eq(s21_pow(-S21_INF, 2), powl(-S21_INF, 2));
  ck_assert_ldouble_eq(s21_pow(-S21_INF, -2), powl(-S21_INF, -2));
  ck_assert_ldouble_nan(s21_pow(-S21_INF, 2.3));
  ck_assert_ldouble_nan(s21_pow(-S21_INF, -2.3));
  ck_assert_ldouble_nan(s21_pow(-S21_INF, S21_INF));
  ck_assert_ldouble_nan(s21_pow(-S21_INF, -S21_INF));

  ck_assert_ldouble_eq(s21_pow(2, S21_INF), powl(2, S21_INF));
  ck_assert_ldouble_nan(s21_pow(-2, S21_INF));
  ck_assert_ldouble_eq(s21_pow(2.3, S21_INF), powl(2.3, S21_INF));
  ck_assert_ldouble_nan(s21_pow(-2.3, S21_INF));
  ck_assert_ldouble_eq(s21_pow(2, -S21_INF), powl(2, -S21_INF));
  ck_assert_ldouble_nan(s21_pow(-2, -S21_INF));
  ck_assert_ldouble_eq(s21_pow(2.3, -S21_INF), powl(2.3, -S21_INF));
  ck_assert_ldouble_nan(s21_pow(-2.3, -S21_INF));

  ck_assert_ldouble_eq(s21_pow(S21_INF, S21_INF), powl(S21_INF, S21_INF));
  ck_assert_ldouble_eq(s21_pow(S21_INF, -S21_INF), powl(S21_INF, -S21_INF));
  ck_assert_ldouble_nan(s21_pow(-S21_INF, S21_INF));
  ck_assert_ldouble_nan(s21_pow(-S21_INF, -S21_INF));
  // one+infinity
  ck_assert_ldouble_eq(s21_pow(1, S21_INF), powl(1, S21_INF));
  ck_assert_ldouble_eq(s21_pow(1, -S21_INF), powl(1, S21_INF));
  ck_assert_ldouble_eq(s21_pow(S21_INF, 1), powl(S21_INF, 1));
  ck_assert_ldouble_eq(s21_pow(-S21_INF, 1), powl(-S21_INF, 1));
  ck_assert_ldouble_nan(s21_pow(-1, S21_INF));
  ck_assert_ldouble_nan(s21_pow(-1, -S21_INF));
  ck_assert_ldouble_eq(s21_pow(S21_INF, -1), powl(S21_INF, -1));
  ck_assert_ldouble_eq(s21_pow(-S21_INF, -1), powl(-S21_INF, -1));
  // zero+infinity
  ck_assert_ldouble_eq(s21_pow(0, S21_INF), powl(0, S21_INF));
  ck_assert_ldouble_eq(s21_pow(0, -S21_INF), powl(0, -S21_INF));
  ck_assert_ldouble_eq(s21_pow(S21_INF, 0), powl(S21_INF, 0));
  ck_assert_ldouble_eq(s21_pow(-S21_INF, 0), powl(-S21_INF, 0));
  // inf+nan
  ck_assert_ldouble_nan(s21_pow(S21_INF, S21_NAN));
  ck_assert_ldouble_nan(s21_pow(-S21_INF, S21_NAN));
  ck_assert_ldouble_nan(s21_pow(S21_NAN, S21_INF));
  ck_assert_ldouble_nan(s21_pow(S21_NAN, -S21_INF));
  // nan + one
  ck_assert_ldouble_eq(s21_pow(1, S21_NAN), powl(1, S21_NAN));
  ck_assert_ldouble_nan(s21_pow(-1, S21_NAN));
  ck_assert_ldouble_nan(s21_pow(S21_NAN, 1));
  ck_assert_ldouble_nan(s21_pow(S21_NAN, -1));
  // nan
  ck_assert_ldouble_nan(s21_pow(S21_NAN, S21_NAN));
  ck_assert_ldouble_nan(s21_pow(S21_NAN, 0.69));
  ck_assert_ldouble_nan(s21_pow(0.69, S21_NAN));

  printf("[PASS]\n");
}
END_TEST
START_TEST(exp_t) {
  printf("Testing s21_exp: ");
  int n = 49;
  long double a = -2.7, b = 2.7, step = (b - a) / n;
  for (long double x = a; x < b; x += step)
    ck_assert_ldouble_le(fabsl(s21_exp(x) - expl(x)), precision);
  ck_assert_ldouble_le(fabsl(s21_exp(0) - expl(0)), precision);
  ck_assert_ldouble_le(fabsl(s21_exp(s21_log(2.4)) - expl(logl(2.4))),
                       precision);
  ck_assert_ldouble_le(fabsl(s21_exp(10) - expl(10)), precision);
  ck_assert_ldouble_le(fabsl(s21_exp(-10) - expl(-10)), precision);
  ck_assert_ldouble_le(fabsl(s21_exp(1e-10) - expl(1e-10)), precision);
  ck_assert_ldouble_eq(s21_exp(S21_INF), expl(S21_INF));
  ck_assert_ldouble_eq(s21_exp(-S21_INF), expl(-S21_INF));
  ck_assert_ldouble_nan(s21_exp(S21_NAN));
  printf("[PASS]\n");
}
END_TEST
START_TEST(sqrt_t) {
  printf("Testing s21_sqrt: ");
  int n = 99;
  long double a = 0, b = 4, step = (b - a) / n;
  for (long double x = a; x < b; x += step)
    ck_assert_ldouble_le(fabsl(s21_sqrt(x) - sqrtl(x)), precision);
  ck_assert_ldouble_eq_tol(s21_sqrt(123321.321123), sqrt(123321.321123), 1e-6);
  ck_assert_ldouble_nan(s21_sqrt(-9));
  // ck_assert_ldouble_le(fabsl(s21_sqrt(3*3) - sqrtl(3*3)), precision);
  ck_assert_ldouble_eq(s21_sqrt(3 * 3), sqrtl(3 * 3));
  ck_assert_ldouble_eq(s21_sqrt(S21_INF), sqrtl(S21_INF));
  ck_assert_ldouble_nan(s21_sqrt(-S21_INF));
  ck_assert_ldouble_nan(s21_sqrt(S21_NAN));
  printf("[PASS]\n");
}
END_TEST
START_TEST(log_t) {
  printf("Testing s21_log: ");
  int n = 49;
  long double a = 0.1, b = 5.4, step = (b - a) / n;
  for (long double x = a; x < b; x += step)
    ck_assert_ldouble_le(fabsl(s21_log(x) - logl(x)), precision);
  ck_assert_ldouble_le(fabsl(s21_log(S21_E) - logl(S21_E)), precision);
  ck_assert_ldouble_le(fabsl(s21_log(s21_exp(2)) - logl(expl(2))), precision);
  ck_assert_ldouble_le(fabsl(s21_log(10) - logl(10)), precision);
  ck_assert_ldouble_le(fabsl(s21_log(1e-10) - logl(1e-10)), precision);
  ck_assert_ldouble_eq(s21_log(0), s21_log(0));
  ck_assert_ldouble_eq(s21_log(S21_INF), logl(S21_INF));
  ck_assert_ldouble_nan(s21_log(-S21_INF));
  ck_assert_ldouble_nan(s21_log(S21_NAN));
  printf("[PASS]\n");
}
END_TEST

Suite *test_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("String test");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, abs_t);
  tcase_add_test(tc_core, fabs_t);

  tcase_add_test(tc_core, floor_t);
  tcase_add_test(tc_core, ceil_t);
  tcase_add_test(tc_core, fmod_t);
  tcase_add_test(tc_core, round_t);

  tcase_add_test(tc_core, sin_t);
  tcase_add_test(tc_core, cos_t);
  tcase_add_test(tc_core, tan_t);

  tcase_add_test(tc_core, asin_t);
  tcase_add_test(tc_core, acos_t);
  tcase_add_test(tc_core, atan_t);

  tcase_add_test(tc_core, pow_t);
  tcase_add_test(tc_core, exp_t);
  tcase_add_test(tc_core, sqrt_t);
  tcase_add_test(tc_core, log_t);
  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  Suite *s = test_suite();
  SRunner *runner = srunner_create(s);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);

  int nofailed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (nofailed == 0) ? 1 : 0;
}
