#include "test.h"

START_TEST(test_01) {
  parametrs co = {0};
  open_and_read_file("obj/lamp.obj", &co);
  s21_translation(&co, 4.3213, 0, 0);
  s21_translation(&co, 0, 532, 0);
  s21_translation(&co, 0, 0, 0.002);
  s21_center(&co);
  s21_translation(&co, -123.52, 5, 0);
  s21_translation(&co, 0, 0, -1345);
  s21_center(&co);
  s21_delete(&co);
}
END_TEST

START_TEST(test_02) {
  parametrs co = {0};
  open_and_read_file("obj/lamp.obj", &co);
  int err = s21_scaling(&co, 0.0);
  s21_delete(&co);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(test_03) {
  parametrs co = {0};
  open_and_read_file("obj/lamp.obj", &co);
  int err = s21_scaling(&co, 11.5);
  s21_center(&co);
  s21_delete(&co);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(test_04) {
  parametrs co = {0};
  open_and_read_file("obj/Gun.obj", &co);
  s21_center(&co);
  s21_rotation(&co, 0.56, 0, -1);
  s21_rotation(&co, -42, 66.3, 0);
  s21_rotation(&co, 0, -545, 12.4);
  s21_delete(&co);
}
END_TEST

void test_transformations(SRunner *runner) {
  Suite *tests = suite_create("test_transformations");
  tests = add_test(tests, test_01);
  tests = add_test(tests, test_02);
  tests = add_test(tests, test_03);
  tests = add_test(tests, test_04);
  srunner_add_suite(runner, tests);
}