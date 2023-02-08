#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <stdint.h>

#define S21_INF 1.0 / 0.0
#define S21_NAN 0.0 / 0.0

#define S21_PI 3.1415926535897931159l
#define S21_PI_2 1.5707963267948966l
#define S21_3PI_2 4.712388980384689l
#define S21_2PI 6.283185307179586l
#define S21_E 2.71828182845904523l
#define S21_LN2 0.69314718055994530l
#define S21_LN10 2.3025850929940456l

#define OCTALC sizeof(long double) / sizeof(int64_t)
#define EXPBITS 0x7FFF
#define MANBITC 63

int s21_abs(int x);
long double s21_fabs(long double x);

long double s21_floor(long double x);
long double s21_ceil(long double x);
long double s21_trunc(long double x);
long double s21_round(long double x);
long double s21_fmod(long double x, long double y);

long double s21_sin(long double x);
long double s21_cos(long double x);
long double s21_tan(long double x);

long double s21_acos(long double x);
long double s21_asin(long double x);
long double s21_atan(long double x);

long double s21_pow2i(long double exp);
long double s21_powi(long double base, long double exp);
long double s21_pow(long double base, long double exp);
long double s21_exp(long double x);
long double s21_sqrt(long double x);
long double s21_log(long double x);

int s21_isfinite(long double x);
int s21_isinf(long double x);
int s21_isnan(long double x);
int s21_iswhole(long double x);

#endif  // SRC_S21_MATH_H_
