#include "s21_math.h"

long double tangent_angles[] = {
    0.78539816339744830961,    0.4636476090008061162,
    0.24497866312686415417,    0.12435499454676143503,
    0.062418809995957348475,   0.031239833430268276253,
    0.015623728620476830803,   0.0078123410601011112965,
    0.0039062301319669718277,  0.0019531225164788186852,
    0.00097656218955931943043, 0.00048828121119489827547,
    0.00024414062014936176402, 0.00012207031189367020424,
    6.1035156174208775022e-05, 3.0517578115526096862e-05,
    1.5258789061315762107e-05, 7.6293945311019702635e-06,
    3.814697265606496283e-06,  1.9073486328101870354e-06,
    9.5367431640596087944e-07, 4.7683715820308885994e-07,
    2.384185791015579825e-07,  1.1920928955078068531e-07,
    5.9604644775390554415e-08, 2.9802322387695303677e-08,
    1.4901161193847655147e-08, 7.4505805969238279873e-09,
    3.7252902984619140453e-09, 1.8626451492309570291e-09,
    9.3132257461547851537e-10, 4.6566128730773925779e-10,
    2.3283064365386962891e-10, 1.1641532182693481445e-10,
    5.8207660913467407227e-11, 2.9103830456733703613e-11,
    1.4551915228366851807e-11, 7.2759576141834259033e-12,
    3.6379788070917129517e-12, 1.8189894035458564758e-12,
    9.0949470177292823792e-13, 4.5474735088646411896e-13,
    2.2737367544323205948e-13, 1.1368683772161602974e-13,
    5.684341886080801487e-14,  2.8421709430404007435e-14,
    1.4210854715202003717e-14, 7.1054273576010018587e-15,
    3.5527136788005009294e-15, 1.7763568394002504647e-15,
    8.8817841970012523234e-16, 4.4408920985006261617e-16,
    2.2204460492503130808e-16, 1.1102230246251565404e-16,
    5.5511151231257827021e-17, 2.7755575615628913511e-17,
    1.3877787807814456755e-17, 6.9388939039072283776e-18,
    3.4694469519536141888e-18, 1.7347234759768070944e-18,
    8.6736173798840354721e-19, 4.336808689942017736e-19,
    2.168404344971008868e-19};

long double chebyshev_sin(long double x) {
  // Chebyshev approximation for sinx summated with Clenshaw alghorithm
  const long double c_sin[] = {
      -0.42476506015273822865,   -0.058224392078514572072,
      0.74564931593694056499,    -0.31504226022478564438,
      0.058247768279542445596,   -0.0062956504847546091678,
      0.00045277117470981463257, -2.3376886594574810396e-05,
      9.1161719852743175551e-07, -2.7852910787037387064e-08,
      6.8556995117086238587e-10, -1.3895858880252567668e-11,
      2.3609810458726357887e-13, -3.4124466240223290358e-15,
      4.248069303240149625e-17,  -4.6033425716743938346e-19,
      4.3822134883976752157e-21, -3.6943087026160027476e-23,
      2.7775492482464429791e-25, -1.8741618426444227021e-27};
  long double bn, bn_1 = 0, bn_2 = 0;
  for (int i = 39; i > 0; i--) {
    long double t = i % 2 ? c_sin[i / 2] : 0;
    bn = t + 2.0 * x * bn_1 - bn_2;
    bn_2 = bn_1;
    bn_1 = bn;
  }
  bn = 2.0 * x * bn_1 - bn_2;
  return (bn - bn_2) / 2.0l;
}
long double cordic_rotation_to0(long double sin, long double cos) {
  // cordic rotations to angle 0 from given vector
  int n = 63;
  long double u[2] = {cos, sin};
  long double alpha = 0, s;
  for (int i = 0; i < n; alpha += s * tangent_angles[i], i++) {
    s = (0 > u[1]) - (0 < u[1]);
    long double v[2];
    v[0] = u[0] - s * s21_pow2i(-i) * u[1];
    v[1] = s * s21_pow2i(-i) * u[0] + u[1];
    u[0] = v[0];
    u[1] = v[1];
  }
  return -alpha;
}
long double cordic_rotation_tox(long double x) {
  // cordic rotation to angle x
  int n = 63;
  long double u[2] = {1, 0};
  long double ysum = 0, s;  // K = 0.60725293500888127872l;
  for (int i = 0; i < n; ysum += s * tangent_angles[i], i++) {
    s = (x > ysum) - (x < ysum);
    long double v[2];
    v[0] = u[0] - s * s21_pow2i(-i) * u[1];
    v[1] = s * s21_pow2i(-i) * u[0] + u[1];
    u[0] = v[0];
    u[1] = v[1];
  }
  return s21_fabs(u[1] / u[0]);
}
long double s21_sin(long double x) {
  if (!s21_isfinite(x)) return S21_NAN;
  x = s21_fmod(x, S21_2PI);
  return chebyshev_sin(x / S21_2PI);
}
long double s21_cos(long double x) {
  if (!s21_isfinite(x)) return S21_NAN;
  return s21_sin(S21_PI_2 - x);
}
long double s21_tan(long double x) {
  if (!s21_isfinite(x)) return S21_NAN;
  long double sign = (x < 0) ? -1 : 1;
  x = s21_fabs(x);
  x = s21_fmod(x, S21_2PI);
  if (x > S21_3PI_2)
    return -sign * cordic_rotation_tox(S21_2PI - x);
  else if (x > S21_PI)
    return sign * cordic_rotation_tox(x - S21_PI);
  else if (x > S21_PI_2)
    return -sign * cordic_rotation_tox(S21_PI - x);
  return cordic_rotation_tox(x) * sign;
}

long double s21_asin(long double x) {
  if (-1 > x || x > 1 || !s21_isfinite(x)) return S21_NAN;
  return cordic_rotation_to0(x, s21_sqrt(1 - x * x));
}
long double s21_acos(long double x) {
  if (-1 > x || x > 1 || !s21_isfinite(x))
    return S21_NAN;
  else if (x < 0)
    return S21_PI - cordic_rotation_to0(s21_sqrt(1 - x * x), -x);
  return cordic_rotation_to0(s21_sqrt(1 - x * x), x);
}
long double s21_atan(long double x) {
  if (s21_isnan(x))
    return S21_NAN;
  else if (x == S21_INF)
    return S21_PI_2;
  else if (x == -S21_INF)
    return -S21_PI_2;
  return s21_asin(x / s21_sqrt(1 + x * x));
}