#include "s21_3dviewer.h"

int open_and_read_file(char *path, parametrs *cordination) {
  FILE *fl = fopen(path, "r");
  int res = 0;
  char str[256];
  s21_delete(cordination);
  if (fl == NULL) {
    printf("File does not exist\n");
    res = -1;
  } else {
    while (fgets(str, 256, fl) != NULL) {
      if (str[strlen(str) - 1] == '\n' || str[strlen(str) - 1] == 13)
        str[strlen(str) - 1] = '\0';
      edit_str(str);
      if (check_v(str) == 1) {
        data_input_v(cordination, str);
      } else if (check_f(str) == 1) {
        data_input_f(cordination, str);
      }
    }
    fclose(fl);
  }
  if (valid_data(cordination) == 0) res = -1;
  return res;
}

int check_value(char *str) {
  unsigned long int i = 0;
  int count_sign = 0, count_point = 0;
  int res = 1;
  while (str[i] != '\0' && res == 1 &&
         ((str[i] >= '0' && str[i] <= '9') || str[i] == '+' || str[i] == '-' ||
          str[i] == '.')) {
    if (str[i] == '+' || str[i] == '-') {
      if (i != 0 || str[i + 1] == '\0') res = 0;
      count_sign++;
    }
    if (str[i] == '.') {
      if (i == 0 || str[i + 1] == '\0') res = 0;
      count_point++;
    }
    if (count_sign == 2 || count_point == 2) break;
    i++;
  }
  if (i != strlen(str)) res = 0;
  return res;
}

int check_v(char *str) { return check_str(str, 'v'); }
int check_f(char *str) { return check_str(str, 'f'); }

int check_str(char *str, char char_for_check) {
  int res = 1;
  int count_numbers = 1;
  if (strlen(str) > 1 && str[0] == char_for_check && str[1] == ' ') {
    char str_for_check[256];
    unsigned long int i = 1;
    while (str[i] == ' ') i++;
    for (; i < strlen(str); i++) {
      int j = 0;
      while (str[i] == ' ') i++;
      while (str[i] != '\0' && str[i] != ' ' && str[i] != 'E') {
        str_for_check[j++] = str[i++];
      }
      if (str[i] == 'E') count_numbers--;
      if (char_for_check != 'v' && str[i] == 'E') {
        res = 0;
        break;
      } else
        str_for_check[j] = '\0';
      if (str[i] == '\0' || str[i] == '\n') break;
      if (check_value(str_for_check) == 0) {
        res = 0;
        break;
      } else
        count_numbers++;
    }
    if (char_for_check == 'v' && count_numbers != 3) res = 0;
  } else
    res = 0;
  return res;
}

void data_input_v(parametrs *p, char *str) {
  p->count_vertices++;
  p->vertices =
      (double *)realloc(p->vertices, p->count_vertices * 3 * sizeof(double));
  unsigned long int i = 1;
  while (str[i] == ' ') i++;
  for (unsigned long int j = 0; i < strlen(str); i++, j++) {
    while (str[i] == ' ') i++;
    p->vertices[3 * (p->count_vertices - 1) + j] = atof(str + i);
    while (i < strlen(str) && str[i] != ' ') i++;
  }
}

void data_input_f(parametrs *p, char *str) {
  int count = count_num(str) * 2;
  p->count_lines += count;
  p->lines = (unsigned int *)realloc(
      p->lines, (p->count_lines + count) * sizeof(unsigned int));
  unsigned long int i = 1;
  while (str[i] == ' ') i++;
  for (unsigned long int j = 0; i < strlen(str); i++, j++) {
    while (str[i] == ' ') i++;
    p->lines[p->count_lines - count + j] = atof(str + i) - 1;
    if (j != 0 && j != strlen(str) - 1) {
      p->lines[p->count_lines - count + j + 1] = atof(str + i) - 1;
      j++;
    }
    while (i < strlen(str) && str[i] != ' ') i++;
  }
  p->lines[p->count_lines - 1] = p->lines[p->count_lines - count];
}

int count_num(char *str) {
  int res = 1;
  int i = 1;
  while (str[i] == ' ') i++;
  for (; str[i] != '\0'; i++) {
    if (str[i] == ' ' && str[i + 1] != ' ' && str[i + 1] != '\0' &&
        str[i + 1] != 13)
      res++;
  }
  return res;
}

void s21_delete(parametrs *A) {
  free(A->lines);
  free(A->vertices);
  A->lines = NULL;
  A->vertices = NULL;
  A->count_lines = 0;
  A->count_vertices = 0;
}

int valid_data(parametrs *p) {
  int flag = 1;
  for (int i = 0; i < (int)p->count_lines; i++) {
    if (p->lines[i] >= p->count_vertices) {
      flag = 0;
      break;
    }
  }
  return flag;
}

void edit_str(char *str) {
  if (strlen(str) > 2 && str[0] == 'f' && str[1] == ' ') {
    int i = 1;
    int j = 1;
    while (str[i] == ' ') {
      i++;
      j++;
    }
    for (; str[i] != '\0'; i++, j++) {
      while (str[i] != '\0' && str[i] != '/') str[j++] = str[i++];
      if (str[i] == '/') {
        while (str[i] != '\0' && str[i] != ' ') {
          i++;
        }
        str[j] = ' ';
      }
    }
    if (str[j] != '\0') {
      str[j - 1] = '\0';
    }
  }
}
