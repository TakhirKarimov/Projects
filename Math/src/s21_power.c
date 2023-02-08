#include "s21_math.h"

long double s21_pow2i(long double exp) {
  union flt {
    long double flt;
    int64_t byte8[OCTALC];
  } d;
  d.flt = 1.0l;
  d.byte8[OCTALC - 1] = (d.byte8[OCTALC - 1] & EXPBITS) + exp;
  return d.flt;
}
long double s21_powi(long double base, long double exp) {
  long double res = 1;
  while (exp > 0) {
    if (s21_fmod(exp, 2)) {
      res *= base;
      exp -= 1;
    } else {
      base *= base;
      exp /= 2;
    }
  }
  return res;
}

long double pade_exp(long double x) {
  // Pade approximation for e^x with 20 terms
  const long double P[] = {1.0l,
                           0.5l,
                           19.0l / 156.0l,
                           1.0l / 52.0l,
                           17.0l / 7696.0l,
                           17.0l / 86580.0l,
                           17.0l / 1212120.0l,
                           1.0l / 1212120.0l,
                           1.0l / 24615360.0l,
                           1.0l / 590768640.0l,
                           1.0l / 16648934400.0l,
                           1.0l / 549414835200.0l,
                           1.0l / 21244040294400.0l,
                           1.0l / 966603833395200.0l,
                           1.0l / 52196607003340800.0l,
                           1.0l / 3392779455217152000.0l,
                           1.0l / 271422356417372160000.0l,
                           1.0l / 27685080354571960320000.0l,
                           1.0l / 3820541088930930524160000.0l,
                           1.0l / 798493087586564479549440000.0l,
                           1.0l / 335367096786357081410764800000.0l};
  long double i = s21_floor(x / S21_LN2 + 0.5l), f = x - i * S21_LN2;
  long double ei, ef, Psum = 0, Qsum = 0;
  ei = s21_pow2i(i);
  long double powx = s21_powi(f, 20), sign = 1;
  for (int j = 20; j >= 0; j--) {
    Psum += powx * P[j];
    Qsum += powx * P[j] * sign;
    powx /= f;
    sign *= -1;
  }
  ef = Psum / Qsum;
  return ei * ef;
}
long double newthon_log(long double x) {
  // Modified Newthon-Raphson solving e^y/2 - ce^-y/2 = 0 where c is x = c*10^n
  long double exp = 0, ln = 1;
  if (x >= 10.0)
    for (; x >= 10.0; x /= 10, exp++) {
    }
  else if (x < 0.1)
    for (; x < 0.1; x *= 10, exp--) {
    }
  for (int i = 0; i < 63; i++)
    ln += 2.0 * (x - s21_exp(ln)) / (x + s21_exp(ln));
  return ln + exp * S21_LN10;
}

long double s21_pow(long double base, long double exp) {
  if (base == 1)
    return 1;
  else if (s21_iswhole(exp) && base == 2.0l)
    return s21_pow2i(exp);
  else if (s21_iswhole(exp) && exp >= 0)
    return s21_powi(base, exp);
  else if (s21_iswhole(exp) && exp < 0)
    return 1 / s21_powi(base, -exp);
  else if (base >= 0)
    return s21_exp(exp * s21_log(base));
  return S21_NAN;
}
long double s21_exp(long double x) {
  if (x == S21_INF)
    return S21_INF;
  else if (x == -S21_INF)
    return 0;
  else if (x == S21_NAN)
    return S21_NAN;
  else if (x == 0)
    return 1.0;
  else
    return pade_exp(x);
}

long double s21_sqrt(long double x) {
  // Newthon's method solving xi^2 - x = 0
  if (x < 0) return S21_NAN;
  long double xn = x / 2;
  for (int i = 0; i < 63 && s21_isfinite(x) && x > 0; i++)
    xn = 0.5l * (xn + x / xn);
  return xn;
}
long double s21_log(long double x) {
  if (x < 0 || s21_isnan(x))
    return S21_NAN;
  else if (x == S21_INF)
    return S21_INF;
  else if (x == 0)
    return -S21_INF;
  else
    return newthon_log(x);
}
