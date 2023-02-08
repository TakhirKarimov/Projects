#ifndef SRC_S21_DBINARY_H_
#define SRC_S21_DBINARY_H_
#define D_NORMAL 0
#define D_NAN 2
#define D_INF 1
#define D_NEGINF -1
#include "s21_dconst.h"

s21_decimal s21_normalize(s21_decimal n);
s21_decimal s21_pow10(unsigned char n);
int s21_eqscale(s21_decimal *value_1, s21_decimal *value_2);

int s21_iszero(s21_decimal val);
int s21_type(s21_decimal a);
void* s21_bincpy(void* dest, void* src);

s21_decimal s21_lshift(s21_decimal val, int shift);
s21_decimal s21_rshift(s21_decimal val, int shift);
s21_decimal s21_not(s21_decimal val);

int s21_bincmp(s21_decimal a, s21_decimal b);
s21_decimal s21_binadd(s21_decimal summand, s21_decimal addend);
s21_decimal s21_binsub(s21_decimal summand, s21_decimal addend);
s21_decimal s21_bindiv(s21_decimal n, s21_decimal d);
s21_decimal s21_binmod(s21_decimal n, s21_decimal d);
s21_decimal s21_binmul(s21_decimal multer, s21_decimal multend);

#endif  //  SRC_S21_DBINARY_H_
