#ifndef SRC_TEST_H_
#define SRC_TEST_H_

#include <check.h>
#include <stdio.h>

#include "../modules/s21_transformations.h"

Suite *add_test(Suite *suite, const TTest *test);

void test_read(SRunner *runner);
void test_transformations(SRunner *runner);

#endif  // SRC_TEST_H_
