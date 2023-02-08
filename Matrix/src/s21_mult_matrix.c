#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || A->rows < 1 || B->rows < 1 || A->columns < 1 ||
      B->columns < 1 || A->matrix == NULL || B->matrix == NULL)
    return ERROR;
  if (A->columns != B->rows) return calculation_error;
  if (s21_create_matrix(A->rows, B->columns, result) != OK) return ERROR;
  for (int i = 0; i < A->rows; i++)
    for (int j = 0; j < B->columns; j++)
      for (int q = 0; q < A->columns; q++)
        result->matrix[i][j] += A->matrix[i][q] * B->matrix[q][j];
  return OK;
}
