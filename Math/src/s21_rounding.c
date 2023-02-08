#include "s21_math.h"

long double s21_trunc(long double x) {
  union flt {
    long double flt;
    int64_t byte8[OCTALC];
  } d;
  d.flt = x;
  short exp, ofs;
  exp = (d.byte8[OCTALC - 1] & EXPBITS) - 16383;
  ofs = MANBITC - exp;
  if (exp < 0) return 0;
  for (unsigned int l = 0; l < OCTALC && ofs > 0; l++)
    for (int b = 0; b < 64 && (int)(b + l * 64) < ofs; b++)
      d.byte8[l] &= ~((int64_t)1 << b);
  return d.flt;
}
long double s21_floor(long double x) {
  if (s21_iswhole(x) || !s21_isfinite(x)) return x;
  return s21_trunc(x) - (x < 0);
}
long double s21_ceil(long double x) {
  if (s21_iswhole(x) || !s21_isfinite(x)) return x;
  return s21_floor(x + 1);
}
long double s21_round(long double x) {
  if (s21_iswhole(x) || !s21_isfinite(x))
    return x;
  else if (x > 0)
    return s21_trunc(x + 0.5l);
  else
    return s21_trunc(x - 0.5l);
}
