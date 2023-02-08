#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_math.h"

START_TEST(test_s21_abs) {
  ck_assert_int_eq(s21_abs(0), abs(0));
  ck_assert_int_eq(s21_abs(-0), abs(-0));
  ck_assert_int_eq(s21_abs(1), abs(1));
  ck_assert_int_eq(s21_abs(-1), abs(-1));
  ck_assert_int_eq(s21_abs(10), abs(10));
  ck_assert_int_eq(s21_abs(-10), abs(-10));
  ck_assert_int_eq(s21_abs(-987654321), abs(-987654321));
  ck_assert_int_eq(s21_abs(987654321), abs(987654321));
}
END_TEST
START_TEST(test_s21_acos) {
  ck_assert_float_eq(s21_acos(0), acos(0));
  ck_assert_float_eq(s21_acos(1), acos(1));
  ck_assert_float_eq(s21_acos(-1), acos(-1));
  ck_assert_ldouble_eq_tol(s21_acos(0.5), acos(0.5), 1e-6);
  ck_assert_ldouble_eq(s21_acos(-1.0), acos(-1.0));
  ck_assert_ldouble_eq_tol(s21_acos(-0.5), acos(-0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(0.0), acos(0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(-0.0), acos(-0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(1.0), acos(1.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_acos(-1.0), acos(-1.0), 1e-6);
  ck_assert_ldouble_nan(acos(10.0));
  ck_assert_ldouble_nan(s21_acos(10.0));
}
END_TEST
START_TEST(test_s21_asin) {
  ck_assert_ldouble_eq_tol(s21_asin(1.0), asin(1.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(-1.0), asin(-1.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(0.0), asin(0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(-0.0), asin(-0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(0.0), asin(0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(-1), asin(-1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_asin(1), asin(1), 1e-6);
  ck_assert_ldouble_nan(asin(10.));
  ck_assert_ldouble_nan(s21_asin(10.));
}
END_TEST
START_TEST(test_s21_fmod) {
  ck_assert_ldouble_eq(s21_fmod(-7.77, -3.0), fmod(-7.77, -3.0));
  ck_assert_ldouble_eq(s21_fmod(-7.66, 2.0), fmod(-7.66, 2.0));
  ck_assert_ldouble_eq(s21_fmod(7.22, -1.0), fmod(7.22, -1.0));
  ck_assert_ldouble_eq(s21_fmod(9.46, 5.0), fmod(9.46, 5.0));
  ck_assert_ldouble_eq(s21_fmod(-12345, -7), fmod(-12345, -7));
  ck_assert_ldouble_eq(s21_fmod(-7, -54321), fmod(-7, -54321));
  ck_assert_ldouble_eq(s21_fmod(-23.15, 3), fmod(-23.15, 3));
  ck_assert_ldouble_eq(s21_fmod(5, -53.54), fmod(5, -53.54));
  ck_assert_ldouble_eq(s21_fmod(33.54, 2), fmod(33.54, 2));
  ck_assert_ldouble_eq(s21_fmod(3, 33.45), fmod(3, 33.45));
  ck_assert_ldouble_eq(s21_fmod(67890, 5), fmod(67890, 5));
  ck_assert_ldouble_eq(s21_fmod(-5, -5), fmod(-5, -5));
  ck_assert_ldouble_eq_tol(s21_atan(-1.0 / 0.0), atan(-1.0 / 0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(1.0 / 0.0), atan(1.0 / 0.0), 1e-6);
  ck_assert_ldouble_nan(fmod(1. / 0., 2.));
  ck_assert_ldouble_nan(s21_fmod(1. / 0., 2.));
}
END_TEST
START_TEST(test_s21_atan) {
  ck_assert_ldouble_eq_tol(s21_atan(0.0), atan(0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-0.0), atan(-0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(1.0), atan(1.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(1.1), atan(1.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-1.0), atan(-1.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-1.1), atan(-1.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(-0.1), atan(-0.1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_atan(0.1), atan(0.1), 1e-6);
}
END_TEST
START_TEST(test_s21_ceil) {
  ck_assert_ldouble_eq(s21_ceil(0), ceil(0));
  ck_assert_ldouble_eq(s21_ceil(0.0), ceil(0.0));
  ck_assert_ldouble_eq(s21_ceil(-0.0), ceil(-0.0));
  ck_assert_ldouble_eq(s21_ceil(-0.12), ceil(-0.12));
  ck_assert_ldouble_eq(s21_ceil(21.21), ceil(21.21));
  ck_assert_ldouble_eq(s21_ceil(-21.21), ceil(-21.21));
  ck_assert_ldouble_eq(s21_ceil(-32.99), ceil(-32.99));
  ck_assert_ldouble_eq(s21_ceil(-7.000000), ceil(-7.000000));
  ck_assert_ldouble_infinite(ceil(1.0 / 0.0));
  ck_assert_ldouble_infinite(s21_ceil(1.0 / 0.0));
}
END_TEST
START_TEST(test_s21_cos) {
  ck_assert_float_eq(s21_cos(0), cos(0));
  ck_assert_float_eq(s21_cos(-1), cos(-1));
  ck_assert_ldouble_eq_tol(s21_cos(0), cos(0), 1e-06);
  ck_assert_ldouble_eq_tol(s21_cos(-1), cos(-1), 1e-06);
  ck_assert_ldouble_eq_tol(s21_cos(S21_PI), cos(M_PI), 1e-06);
  ck_assert_ldouble_eq_tol(s21_cos(S21_PI * 3.0 / 2.0), cos(M_PI * 3.0 / 2.0),
                           1e-06);
  ck_assert_ldouble_nan(cos(-S21_INF));
  ck_assert_ldouble_nan(s21_cos(-S21_INF));
  ck_assert_ldouble_nan(cos(S21_INF));
  ck_assert_ldouble_nan(s21_cos(S21_INF));
  ck_assert_ldouble_nan(cos(S21_NAN));
  ck_assert_ldouble_nan(s21_cos(S21_NAN));
}
END_TEST
START_TEST(test_s21_exp) {
  ck_assert_ldouble_eq_tol(s21_exp(0), exp(0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(1), exp(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(3), exp(3), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(-3), exp(-3), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(7.000), exp(7.000), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(-7.000), exp(-7.000), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(-0.07000), exp(-0.07000), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(12.3123123), exp(12.3123123), 1e-6);
  ck_assert_ldouble_eq_tol(s21_exp(-S21_INF), exp(-S21_INF), 1e-06);
  ck_assert_ldouble_eq_tol(s21_exp(-S21_INF), expl(-S21_INF), 1e-06);
  ck_assert_ldouble_infinite(exp(S21_INF));
  ck_assert_ldouble_infinite(s21_exp(S21_INF));
}
END_TEST

START_TEST(test_s21_fabs) {
  ck_assert_ldouble_eq(s21_fabs(0.), fabs(0.));
  ck_assert_ldouble_eq(s21_fabs(0.000001), fabs(0.000001));
  ck_assert_ldouble_eq(s21_fabs(11.11), fabs(11.11));
  ck_assert_ldouble_eq(s21_fabs(-11.11), fabs(-11.11));
  ck_assert_ldouble_eq(s21_fabs(-21.000345), fabs(-21.000345));
  ck_assert_ldouble_eq(s21_fabs(-214133127.543), fabs(-214133127.543));
  ck_assert_ldouble_eq(s21_fabs(123123131.2357), fabs(123123131.2357));
  ck_assert_ldouble_eq(fabs(-21474.), fabs(-21474.));
}
END_TEST
START_TEST(test_s21_floor) {
  ck_assert_ldouble_eq(s21_floor(0), floor(0));
  ck_assert_ldouble_eq(s21_floor(-0), floor(-0));
  ck_assert_ldouble_eq(s21_floor(7.00000), floor(7.00000));
  ck_assert_ldouble_eq(s21_floor(-7.00000), floor(-7.00000));
  ck_assert_ldouble_eq(s21_floor(44.21), floor(44.21));
  ck_assert_ldouble_eq(s21_floor(22.11), floor(22.11));
  ck_assert_ldouble_eq(s21_floor(-21.21), floor(-21.21));
  ck_assert_ldouble_infinite(floor(INFINITY));
  ck_assert_ldouble_infinite(s21_floor(S21_INF));
}
END_TEST
START_TEST(test_s21_log) {
  ck_assert_ldouble_eq_tol(s21_log(0.5), log(0.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(0.001), log(0.001), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(1.0), log(1.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(1.5), log(1.5), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(100), log(100), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(S21_PI / 3), log(S21_PI / 3), 1e-6);
  ck_assert_ldouble_eq_tol(s21_log(9.123123e6), log(9.123123e6), 1e-6);
  ck_assert_ldouble_nan(log(-10.0));
  ck_assert_ldouble_nan(s21_log(-10.0));
  ck_assert_ldouble_infinite(log(1.0 / 0.0));
  ck_assert_ldouble_infinite(s21_log(1.0 / 0.0));
  ck_assert_ldouble_infinite(log(0.0));
  ck_assert_ldouble_infinite(s21_log(0.0));
}
END_TEST
START_TEST(test_s21_sin) {
  ck_assert_ldouble_eq_tol(s21_sin(0), sin(0), 1e-06);
  ck_assert_ldouble_eq_tol(s21_sin(0.0), sin(0.0), 1e-06);
  ck_assert_ldouble_eq_tol(s21_sin(S21_PI / 2), sin(S21_PI / 2), 1e-06);
  ck_assert_ldouble_eq_tol(s21_sin(S21_PI / 3), sin(S21_PI / 3), 1e-06);
  ck_assert_ldouble_eq_tol(s21_sin(3 * S21_PI / 2), sin(3 * S21_PI / 2), 1e-06);
  ck_assert_ldouble_eq_tol(s21_sin(2 * S21_PI), sin(2 * S21_PI), 1e-06);
  ck_assert_ldouble_eq_tol(s21_sin(-2 * S21_PI), sin(-2 * S21_PI), 1e-06);
  ck_assert_ldouble_eq_tol(s21_sin(-3 * S21_PI), sin(-3 * S21_PI), 1e-06);
  ck_assert_ldouble_eq_tol(s21_sin(-S21_PI), sin(-S21_PI), 1e-06);
}
END_TEST
START_TEST(test_s21_sqrt) {
  ck_assert_ldouble_eq_tol(s21_sqrt(0.0), sqrt(0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(-0.0), sqrt(-0.0), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(1), sqrt(1), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(1.000), sqrt(1.000), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(0.0100), sqrt(0.0100), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(10e+12), sqrt(10e+12), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(456.321e-12), sqrt(456.321e-12), 1e-6);
  ck_assert_ldouble_eq_tol(s21_sqrt(123321.321123), sqrt(123321.321123), 1e-6);
  ck_assert_ldouble_nan(sqrt(S21_NAN));
  ck_assert_ldouble_nan(s21_sqrt(S21_NAN));
  ck_assert_ldouble_infinite(sqrt(S21_INF));
  ck_assert_ldouble_nan(s21_sqrt(-S21_INF));
}
END_TEST

START_TEST(test_s21_tan) {
  ck_assert_ldouble_eq_tol(s21_tan(0), tan(0), 1e-06);
  ck_assert_ldouble_eq_tol(s21_tan(0.0), tan(0.0), 1e-06);
  ck_assert_ldouble_eq_tol(s21_tan(-2 * S21_PI), tan(-2 * S21_PI), 1e-06);
  ck_assert_ldouble_eq_tol(s21_tan(2 * S21_PI), tan(2 * S21_PI), 1e-06);
  ck_assert_ldouble_eq_tol(s21_tan(3 * S21_PI / 3), tan(3 * S21_PI / 3), 1e-06);
  ck_assert_ldouble_eq_tol(s21_tan(S21_PI / 3), tan(S21_PI / 3), 1e-06);
  ck_assert_ldouble_eq_tol(s21_tan(S21_PI), tan(S21_PI), 1e-06);
}
END_TEST
START_TEST(test_s21_pow) {
  ck_assert_ldouble_eq(s21_pow(0, 0), pow(0, 0));
  ck_assert_ldouble_eq(s21_pow(0, -1), pow(0, -1));
  ck_assert_ldouble_eq(s21_pow(0, 1), pow(0, 1));
  ck_assert_ldouble_eq(s21_pow(1, 0), pow(1, 0));
  ck_assert_ldouble_eq(s21_pow(-1, 1), pow(-1, 1));
  ck_assert_ldouble_eq(s21_pow(-1, 2), pow(-1, 2));
  ck_assert_ldouble_eq(s21_pow(0.5, S21_INF), pow(0.5, S21_INF));
  ck_assert_ldouble_eq(s21_pow(0.5, -S21_INF), pow(0.5, -S21_INF));
  ck_assert_ldouble_eq(s21_pow(S21_NAN, 0), pow(S21_NAN, 0));
  ck_assert_ldouble_eq(s21_pow(S21_INF, 0), pow(S21_INF, 0));
  ck_assert_ldouble_eq(s21_pow(S21_INF, -1), pow(S21_INF, -1));
  ck_assert_ldouble_eq(s21_pow(0, S21_INF), pow(0, S21_INF));
  ck_assert_ldouble_nan(s21_pow(-1, -S21_INF));
  ck_assert_ldouble_eq(s21_pow(1, -S21_INF), pow(1, -S21_INF));
  ck_assert_ldouble_eq(s21_pow(2, S21_INF), pow(2, S21_INF));
  ck_assert_ldouble_nan(s21_pow(-2, S21_INF));
  ck_assert_ldouble_eq(s21_pow(2, -S21_INF), pow(2, -S21_INF));
  ck_assert_ldouble_nan(s21_pow(-2, -S21_INF));
  ck_assert_ldouble_eq(s21_pow(S21_INF, S21_INF), pow(S21_INF, S21_INF));
  ck_assert_ldouble_eq(s21_pow(S21_INF, -S21_INF), pow(S21_INF, -S21_INF));
  ck_assert_ldouble_nan(s21_pow(-S21_INF, S21_INF));
  ck_assert_ldouble_nan(s21_pow(-S21_INF, -S21_INF));
  ck_assert_ldouble_nan(pow(-1.5, -2.5));
  ck_assert_ldouble_nan(s21_pow(-1.5, -2.5));
  ck_assert_ldouble_eq(s21_pow(-S21_INF, -3.), s21_pow(-S21_INF, -3.));
  ck_assert_ldouble_eq(s21_pow(-S21_INF, 3.), s21_pow(-S21_INF, 3.));
  ck_assert_ldouble_eq(s21_pow(5., 3.), s21_pow(5., 3.));
  ck_assert_ldouble_eq(s21_pow(5.5, -3.1), s21_pow(5.5, -3.1));
}
END_TEST
// for (int i = 0; i < 5; ++i) {{
//     double f = rand() {/ RAND_MAX, g = rand() {/ RAND_MAX + 1;
//     f = -i + f * 2 * i;
//     ck_assert_ldouble_eq(s21_pow(f, g), s21_pow(f, g));
// }
int main(void) {
  Suite *suite =
      suite_create("UNITS");  // test suite - это набор тестовых случаев
  TCase *tcase =
      tcase_create("TESTS");  // test case — это набор тестовых примеров
  SRunner *srunner = srunner_create(
      suite);  // Suite runner - это функция, которая берет набор тестов
               // и запускает все тестовые случаи и их тестовые функции
  int val = 0;

  suite_add_tcase(suite, tcase);
  tcase_add_test(tcase, test_s21_sin);
  tcase_add_test(tcase, test_s21_cos);
  tcase_add_test(tcase, test_s21_tan);
  tcase_add_test(tcase, test_s21_asin);
  tcase_add_test(tcase, test_s21_acos);
  tcase_add_test(tcase, test_s21_atan);
  tcase_add_test(tcase, test_s21_exp);
  tcase_add_test(tcase, test_s21_log);
  tcase_add_test(tcase, test_s21_sqrt);
  tcase_add_test(tcase, test_s21_pow);
  tcase_add_test(tcase, test_s21_fmod);
  tcase_add_test(tcase, test_s21_ceil);
  tcase_add_test(tcase, test_s21_floor);
  tcase_add_test(tcase, test_s21_abs);
  tcase_add_test(tcase, test_s21_fabs);

  // Запуск всех наборов тестов (suite - набор). CK_NORMAL - что бы выводить
  // только неудачные тесты.
  srunner_set_fork_status(srunner, CK_NOFORK);
  srunner_run_all(srunner, CK_NORMAL);
  // Количество проваленных тестов.
  val = srunner_ntests_failed(srunner);
  // Освобождаем память срунеру, при этом suite и tcase освобождать почему то
  // не нужно
  srunner_free(srunner);
  return val == 0 ? 0 : 1;
}
