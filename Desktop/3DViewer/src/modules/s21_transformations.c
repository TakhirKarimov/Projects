#include "s21_transformations.h"

void s21_translation(parametrs *A, double x, double y, double z) {
  for (long int i = 0; i < (int)A->count_vertices; i++) {
    A->vertices[i * 3 + 0] += x;
    A->vertices[i * 3 + 1] += y;
    A->vertices[i * 3 + 2] += z;
  }
}

void s21_rotation(parametrs *A, double angle_x, double angle_y,
                  double angle_z) {
  double temp_x = 0;
  double temp_y = 0;
  double temp_z = 0;
  for (long int i = 0; i < (int)A->count_vertices; i++) {
    temp_x = A->vertices[i * 3 + 0];
    temp_y = A->vertices[i * 3 + 1];
    temp_z = A->vertices[i * 3 + 2];
    if (angle_x) {
      A->vertices[i * 3 + 1] = cos(angle_x) * temp_y - sin(angle_x) * temp_z;
      A->vertices[i * 3 + 2] = sin(angle_x) * temp_y + cos(angle_x) * temp_z;
    }
    if (angle_y) {
      A->vertices[i * 3 + 0] = cos(angle_y) * temp_x + sin(angle_y) * temp_z;
      A->vertices[i * 3 + 2] = cos(angle_y) * temp_z - sin(angle_y) * temp_x;
    }
    if (angle_z) {
      A->vertices[i * 3 + 0] = cos(angle_z) * temp_x + sin(angle_z) * temp_y;
      A->vertices[i * 3 + 1] = cos(angle_z) * temp_y - sin(angle_z) * temp_x;
    }
  }
}

int s21_scaling(parametrs *A, double factor) {
  int err = 1;
  if (factor) {
    err = 0;
    for (long int i = 0; i < (int)A->count_vertices; i++) {
      for (int j = 0; j < 3; j++) {
        A->vertices[i * 3 + j] *= factor;
      }
    }
  }
  return err;
}

void s21_center(parametrs *A) {
  double x_max = A->vertices[0], x_min = A->vertices[0];
  double y_max = A->vertices[1], y_min = A->vertices[1];
  double z_max = A->vertices[2], z_min = A->vertices[2];
  for (long int i = 1; i < (int)A->count_vertices; i++) {
    if (A->vertices[i * 3 + 0] > x_max) x_max = A->vertices[i * 3 + 0];
    if (A->vertices[i * 3 + 0] < x_min) x_min = A->vertices[i * 3 + 0];
    if (A->vertices[i * 3 + 1] > y_max) y_max = A->vertices[i * 3 + 1];
    if (A->vertices[i * 3 + 1] < y_min) y_min = A->vertices[i * 3 + 1];
    if (A->vertices[i * 3 + 2] > z_max) z_max = A->vertices[i * 3 + 2];
    if (A->vertices[i * 3 + 2] < z_min) z_min = A->vertices[i * 3 + 2];
  }
  double max_height = x_max - x_min;
  if (y_max - y_min > max_height) max_height = y_max - y_min;
  if (z_max - z_min > max_height) max_height = z_max - z_min;
  s21_translation(A, -(x_max + x_min) / 2, -(y_max + y_min) / 2,
                  -(z_max + z_min) / 2);
  s21_scaling(A, 1 / max_height);
}
