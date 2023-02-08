#include <math.h>

#include "s21_dbinary.h"
#include "s21_dconst.h"
#include "s21_decimal.h"
#define MAX 4294967295

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  *dst = 0;
  double dst1 = 0.0;
  double ten = 10.0;
  int q = 0, flag = 0;
  if (!s21_type(src)) {
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 32; i++) {
        if (src.bits32[j] & (1 << i)) dst1 += pow(2, q);
        q++;
      }
    }
    while (src.bits8[14] != 0) {
      dst1 /= ten;
      src.bits8[14]--;
    }
    if (src.bits8[15]) dst1 = -dst1;
  } else {
    flag = 1;
    dst1 = 0;
  }
  *dst = (float)dst1;
  return flag;
}
