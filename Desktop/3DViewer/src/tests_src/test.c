#include "test.h"

// Добавление теста
Suite *add_test(Suite *suite, const TTest *test) {
  TCase *test_case;
  test_case = tcase_create(test->name);
  tcase_add_test(test_case, test);
  suite_add_tcase(suite, test_case);
  return suite;
}

int main(void) {
  SRunner *runner = srunner_create(suite_create(""));

  // test_center(runner);
  test_read(runner);
  test_transformations(runner);
  // test_rotation(runner);
  // test_scaling(runner);
  // test_translation(runner);

  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_set_log(runner, "test.log");
  srunner_run_all(runner, CK_NORMAL);
  int number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (number_failed == 0) ? 0 : 1;
}
