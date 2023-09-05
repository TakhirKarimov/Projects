#ifndef S21_TRANSFORMATIONS_H
#define S21_TRANSFORMATIONS_H

#include <math.h>

#include "s21_3dviewer.h"

void s21_translation(parametrs *A, double x, double y, double z);
void s21_rotation(parametrs *A, double angle_x, double angle_y, double angle_z);
int s21_scaling(parametrs *cordination, double factor);
void s21_center(parametrs *A);

#endif  // S21_TRANSFORMATIONS_H
