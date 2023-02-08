#include "s21_math.h"

int s21_abs(int x) {
  if (x < 0)
    return -x;
  else
    return x;
}
long double s21_fabs(long double x) {
  if (x < 0)
    return -x;
  else
    return x;
}
long double s21_fmod(long double x, long double y) {
  long double i = s21_trunc(x / y), ret = x;
  if (!s21_isinf(y) || !s21_isfinite(x)) {
    ret = x - i * y;
  }
  return ret;
}

int s21_isfinite(long double x) {
  return x == x && x < S21_INF && x > -S21_INF;
}
int s21_isinf(long double x) { return x == S21_INF || x == -S21_INF; }
int s21_isnan(long double x) { return !(x == x); }
int s21_iswhole(long double x) {
  if (!s21_isfinite(x))
    return 0;
  else if (!x)
    return 1;
  union flt {
    long double flt;
    int64_t byte8[OCTALC];
  } d;
  d.flt = x;
  short exp, ofs;
  short hbyte = OCTALC - 1;
  exp = (d.byte8[hbyte] & EXPBITS) - 16383;
  ofs = MANBITC - exp;
  if (exp < 0) {
    return 0;
  }
  for (int l = 0; l < hbyte + 1 && ofs > 0; l++)
    for (int b = 0; b < 64 && (b + l * 64) < ofs; b++)
      if (d.byte8[l] & ((int64_t)1 << b)) {
        return 0;
      }
  return 1;
}
