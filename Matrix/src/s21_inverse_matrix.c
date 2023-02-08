#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || A->matrix == NULL || A->rows < 1 || A->columns < 1 ||
      result == NULL)
    return ERROR;
  if (A->rows != A->columns) return calculation_error;
  double det = 0;
  s21_determinant(A, &det);
  if (det == 0) return calculation_error;
  matrix_t tmp = {0};
  s21_calc_complements(A, result);
  s21_transpose(result, &tmp);
  s21_remove_matrix(result);
  s21_mult_number(&tmp, 1 / det, result);
  s21_remove_matrix(&tmp);
  return OK;
}