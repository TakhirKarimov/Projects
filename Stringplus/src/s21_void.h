#ifndef SRC_VOID_H_
#define SRC_VOID_H_

#include "s21_string.h"

// вспомогательные функции
s21_size_t s21_len(const char* s);
void s21_trim_before_after(const char *src, const char *trim_chars, s21_size_t* count, s21_size_t* recount);
// фукнции для задания
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
//void *s21_insert(const char *src, const char *str, size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

#endif // SRC_VOID_H_