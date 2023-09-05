#include "test.h"

START_TEST(test_01) {
  parametrs co = {0};
  int res = open_and_read_file("obj/lamp.obj", &co);
  ck_assert_int_eq(res, 0);
  s21_delete(&co);
}
END_TEST

START_TEST(test_02) {
  parametrs co = {0};
  int res = open_and_read_file("obj/lamp.obj", &co);
  ck_assert_int_eq(res, 0);
  s21_delete(&co);
}
END_TEST

START_TEST(test_03) {
  parametrs co = {0};
  int res = open_and_read_file("obj/hand.obj", &co);
  ck_assert_int_eq(res, 0);
  s21_delete(&co);
}
END_TEST

START_TEST(test_04) {
  parametrs co = {0};
  int res = open_and_read_file("obj/pyramid.obj", &co);
  ck_assert_int_eq(res, 0);
  s21_delete(&co);
}
END_TEST

START_TEST(test_05) {
  parametrs co = {0};
  int res = open_and_read_file("none", &co);
  ck_assert_int_eq(res, -1);
  s21_delete(&co);
}
END_TEST

void test_read(SRunner *runner) {
  Suite *tests = suite_create("test_read");
  add_test(tests, test_01);
  add_test(tests, test_02);
  add_test(tests, test_03);
  add_test(tests, test_04);
  add_test(tests, test_05);
  srunner_add_suite(runner, tests);
}
