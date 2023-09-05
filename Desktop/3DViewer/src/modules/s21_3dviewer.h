#ifndef S21_3DVIEWER_H
#define S21_3DVIEWER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct parametrs {  // Считываем данные с файла в эту структуру
  unsigned long int count_vertices;
  double *vertices;
  unsigned long int count_lines;
  unsigned int *lines;
} parametrs;

int open_and_read_file(char *path, parametrs *cordination);
int check_value(char *str);
int check_str(char *str, char char_for_check);
int check_v(char *str);
int check_f(char *str);
void data_input_v(parametrs *p, char *str);
void data_input_f(parametrs *p, char *str);
int count_num(char *str);
void s21_print(parametrs *A);
void s21_delete(parametrs *A);
void edit_str(char *str);
int valid_data(parametrs *p);

#endif  // S21_3DVIEWER_H
