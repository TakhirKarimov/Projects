#include <stdarg.h>
#include <stdio.h>
#include <string.h>

typedef struct flags {
  int plus;
  int minus;
  int space;
  int zero;
  int num_width;
  int num_accuracy;
  int start_count;
  int h;
  int l;
  int u;
} flags;

int s21_sprintf(char *, const char *, ...);
int itoa(char *buff, long int num, flags *fl);
int sp_s(char *buff, char *str, flags *fl);
int ftoa(char *buff, double num, flags *fl);
void zeroing_flags(flags *fl);
int shift(char *buff, flags *fl, int buff_c);

int s21_sprintf(char *buff, const char *str, ...) {
  int buff_c = 0;
  int str_c = 0;
  va_list p;
  va_start(p, str);
  flags fl = {0};
  while (str[str_c] != '\0') {
    if (str[str_c] != '%') {
      buff[buff_c] = str[str_c];
    }  // if
    else {
      str_c++;
      while (str[str_c] == ' ' || str[str_c] == '+' || str[str_c] == '-') {
        if (str[str_c] == ' ') fl.space = 1;
        if (str[str_c] == '-') fl.minus = 1;
        if (str[str_c] == '+') fl.plus = 1;
        str_c++;
      }
      while (str[str_c] >= '0' && str[str_c] <= '9') {
        fl.num_width = fl.num_width * 10 + (str[str_c] - 48);
        str_c++;
      }
      fl.start_count = buff_c;
      if (str[str_c] == '.') {
        fl.zero = 1;
        str_c++;
        while (str[str_c] >= '0' && str[str_c] <= '9') {
          fl.num_accuracy = fl.num_accuracy * 10 + (str[str_c] - 48);
          str_c++;
        }
      }
      if (str[str_c] == 'l' || str[str_c] == 'h') {
        if (str[str_c] == 'l')
          fl.l = 1;
        else
          fl.h = 1;
        str_c++;
      }
      switch (str[str_c]) {
        case 'd':
        case 'i':;
          char *ptr = &buff[buff_c];
          if (fl.l == 1)
            buff_c += itoa(ptr, va_arg(p, long int), &fl);
          else
            buff_c += itoa(ptr, va_arg(p, int), &fl);
          break;
        case 'f':;
          char *ptr_f = &buff[buff_c];
          buff_c += ftoa(ptr_f, va_arg(p, double), &fl);
          break;
        case 'u':;
          char *ptr_u = &buff[buff_c];
          fl.u = 1;
          if (fl.l == 1)
            buff_c += itoa(ptr_u, va_arg(p, long unsigned int), &fl);
          else
            buff_c += itoa(ptr_u, va_arg(p, unsigned int), &fl);
          break;
        case 'c':
          buff[buff_c] = va_arg(p, int);
          break;
        case '%':
          buff[buff_c] = '%';
          break;
        case 's':;
          char *ptr_s = &buff[buff_c];
          buff_c += sp_s(ptr_s, va_arg(p, char *), &fl);
          break;
        default:
          buff[buff_c] = str[str_c];
          break;
      }  // switch
      if (fl.minus == 1 && fl.num_width > 0) {
        for (int i = buff_c - fl.start_count + 1; i < fl.num_width; i++) {
          buff[++buff_c] = ' ';
        }
      }
      if (fl.minus == 0 && fl.num_width > 0) {
        char *ptr = &buff[fl.start_count];
        buff_c += shift(ptr, &fl, buff_c);
      }
    }  // else
    buff_c++;
    str_c++;
    zeroing_flags(&fl);
  }  // while
  buff[buff_c] = '\0';
  return buff_c;
}

int itoa(char *buff, long int num, flags *fl) {
  if (fl->h == 1 && fl->u == 0) {
    if (num > 32767) {
      int div = num / 32768;
      div = (fl->u == 1 && div - 2 > 0) ? div - 2 : div;
      div = (div % 2 == 0) ? div : div + 1;
      num = num - (32768 * div);
    }
    if (num < 32768 * (-1)) {
      int div = -num / 32768;
      div = (div % 2 == 0) ? div : div + 1;
      num = num + (32768 * div);
    }
  }
  if (fl->u == 1 && fl->l == 0 && fl->h == 1) {
    if (num > 65535) {
      while (num >= 65536) {
        num -= 65536;
      }
    }
  }
  long int tmp_num = num;
  int flag = 0;
  int i = 0;
  if (num == 0 && fl->zero == 1) {
    if (fl->plus == 1) buff[i++] = '+';
    int j = i;
    while (j <= fl->num_accuracy + i) buff[j++] = '0';
    return fl->num_accuracy + i - 1;
  }
  if (fl->plus == 1 && num >= 0) {
    buff[0] = '+';
    i++;
    fl->space = 0;
    flag = 1;
  }
  if (fl->space == 1 && num >= 0) {
    buff[0] = ' ';
    i++;
    flag = 1;
  }
  if (num < 0) {
    num = -num;
    tmp_num = -tmp_num;
    buff[i] = '-';
    i++;
    flag = 1;
  }
  if (num == 0 && fl->zero == 0) {
    buff[i++] = '0';
    return i - 1;
  }
  while (num != 0) {
    buff[i] = num % 10 + 48;
    num /= 10;
    i++;
  }
  if (tmp_num != 0) i--;
  int end = i;
  int j = 0;
  if (buff[0] == '-' || buff[0] == '+' || buff[0] == ' ') j += 1;
  for (; j <= end / 2; j++) {
    char temp = buff[i];
    buff[i] = buff[j];
    buff[j] = temp;
    i--;
  }
  if (fl->zero == 1) {
    j = 0;
    if (end < fl->num_accuracy) {
      int start = 0;
      if (flag == 1) {
        start = 1;
        fl->num_accuracy += 2;
        j = 1;
      }
      for (i = end; i >= 0; i--, j++) {
        buff[fl->num_accuracy - j - 1] = buff[i];
      }
      if (tmp_num == 0) fl->num_accuracy += 1;
      for (i = start; i < fl->num_accuracy - end - 1; i++) buff[i] = '0';
      if (tmp_num == 0) fl->num_accuracy--;
      end = fl->num_accuracy - start - 1;
    }
  }
  if (end == 0 && tmp_num == 0) end = -1;
  return end;
}

int sp_s(char *buff, char *str, flags *fl) {
  int count = 0;
  while (str[count] != '\0') {
    buff[count] = str[count];
    count++;
  }
  count -= 1;
  if (fl->zero == 1) {
    if (count > fl->num_accuracy) count = fl->num_accuracy - 1;
    if (fl->num_accuracy == -1) count = 0;
  }
  return count;
}

int ftoa(char *buff, double num, flags *fl) {
  int check = 0;
  if (num < 0) {
    fl->plus = 0;
    buff[0] = '-';
    check = 1;
    num = -num;
    buff++;
  }
  int count = 0;
  long int first_part = num;
  long double second_part = num - first_part;
  if (second_part < 0) second_part = -second_part;
  int tmp = fl->zero;
  fl->zero = 0;
  if (first_part == 0 && num < 0) {
    buff[0] = '-';
    buff++;
  }
  count += itoa(buff, first_part, fl);
  int size_whole = count + 1;
  int size_fract_part = 0;
  buff[++count] = '.';
  if (tmp == 0)
    fl->num_accuracy = 6;
  else if (tmp == 1 && fl->num_accuracy == 0)
    count--;
  while (size_fract_part < fl->num_accuracy) {
    buff[++count] = (int)(second_part * 10) + 48;
    second_part = second_part * 10 - (int)(second_part * 10);
    size_fract_part++;
  }

  if (second_part > 0.5) {
    buff[count] += 1;
    for (int i = count; i > size_whole + 1; i--) {
      if (buff[i] == 58) {
        buff[i] = '0';
        buff[i - 1] += 1;
      }
    }
  }
  if (buff[size_whole + 1] == 58) {
    buff[size_whole + 1] = '0';
    buff[size_whole - 1] += 1;
  }
  if (buff[size_whole - 1] == 58) {
    for (int i = size_whole - 1; i > 0; i--) {
      buff[i] = '0';
      buff[i - 1] += 1;
    }
  }
  if (buff[0] == 58) {
    buff[0] = '0';
    for (int i = count + 1; i >= 1; i--) {
      buff[i] = buff[i - 1];
    }
    count++;
    buff[0] = '1';
  }

  if (check == 1) {
    count++;
  }
  return count;
}

void zeroing_flags(flags *fl) {
  fl->minus = 0;
  fl->num_width = 0;
  fl->num_accuracy = 0;
  fl->start_count = 0;
  fl->plus = 0;
  fl->space = 0;
  fl->h = 0;
  fl->l = 0;
  fl->zero = 0;
  fl->u = 0;
}

int shift(char *buff, flags *fl, int buff_c) {
  int ret = fl->num_width + fl->start_count - buff_c - 1;
  if (ret <= 0) {
    ret = 0;
  } else {
    buff_c = buff_c - fl->start_count + 1;
    for (int i = 0, j = buff_c; i < buff_c; i++, j--) {
      buff[fl->num_width - i - 1] = buff[j - 1];
    }
    for (int i = 0; i < fl->num_width - buff_c; i++) {
      buff[i] = ' ';
    }
  }
  return ret;
}
