#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  if (A == NULL || A->rows < 1 || A->columns < 1 || A->matrix == NULL)
    return ERROR;
  if (A->rows != A->columns) return calculation_error;
  int size = A->rows;
  if (size == 1) {
    *result = A->matrix[0][0];
  } else if (size == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
  } else {
    matrix_t tmp = {0};
    s21_create_matrix(size - 1, size - 1, &tmp);
    double sign = 1;
    double tmp_res = 0;
    *result = 0;
    for (int i = 0; i < size; i++) {
      matrix_without_row_column(A, &tmp, 0, i);
      s21_determinant(&tmp, &tmp_res);
      *result += sign * A->matrix[0][i] * tmp_res;
      sign = -sign;
    }
    s21_remove_matrix(&tmp);
  }
  return OK;
}

void matrix_without_row_column(matrix_t *A, matrix_t *tmp, int del_row,
                               int del_column) {
  int A_i = 0, A_j = 0, tmp_i = 0, tmp_j = 0;
  for (; A_i < A->rows; A_i++, tmp_i++) {
    tmp_j = 0;
    A_j = 0;
    if (A_i == del_row) A_i++;
    if (A_i == A->rows) break;
    for (; A_j < A->columns; A_j++, tmp_j++) {
      if (A_j == del_column) A_j++;
      if (A_j == A->columns) break;
      tmp->matrix[tmp_i][tmp_j] = A->matrix[A_i][A_j];
    }
  }
}