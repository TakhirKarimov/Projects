#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_len 1000
#include "s21_grep.h"

int main(int argc, char *argv[]) {
  int files[40];
  int templates[40];
  flags fl = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  get_opt(argc, argv, &fl);
  int count_of_files = search_files(argc, argv, files, &fl);
  int count_of_templates = search_templates(argc, argv, templates, &fl);
  for (int i = 0; i < count_of_files; i++) {
    FILE *f = fopen(argv[files[i]], "r");
    if (f == NULL || argc == 1) {
      if (fl.flag_s == 0) {
        printf("n/a");
        if (i != count_of_files - 1) printf("\n");
      }
    } else {
      char string[1000];
      int count_for_c = 0;
      int count_of_lines = 0;
      int check_line_break = 0;
      fl.stop = 0;
      while (fgets(string, 1000, f) != NULL) {
        count_of_lines++;
        for (int j = 0; j < count_of_templates; j++) {
          if (fl.flag_l == 1 &&
              (flag_l(string, argv[templates[j]], &fl, argv[files[i]]) == 1)) {
            break;
          }
          if (fl.flag_c == 1) {
            flag_c_calc(string, argv[templates[j]], &fl, &count_for_c);
          }
          if (fl.flag_i == 1 || fl.flag_v == 1) {
            check_line_break = flag_i_flag_v(string, argv[templates[j]], &fl,
                                             count_of_files, argv[files[i]]);
            if (j == count_of_templates - 1 &&
                string[strlen(string) - 1] != '\n' && check_line_break == 1)
              printf("\n");
          }
          if (fl.flag_n == 1) {
            check_line_break =
                flag_n(string, argv[templates[j]], &fl, count_of_lines,
                       count_of_files, argv[files[i]]);
            if (j == count_of_templates - 1 &&
                string[strlen(string) - 1] != '\n' && check_line_break == 1)
              printf("\n");
          }
          if (fl.flag_o == 1 && fl.flag_n == 0 && fl.flag_i == 0 &&
              fl.flag_v == 0) {
            check_line_break = flag_o(&fl, string, argv[templates[j]],
                                      count_of_files, argv[files[i]]);
          }
          if (sum_flags(&fl) == 0) {
            if (grep(string, argv[templates[j]]) == 1) {
              path(count_of_files, argv[files[i]], &fl);
              printf(string);
              if (j == count_of_templates - 1 &&
                  string[strlen(string) - 1] != '\n')
                printf("\n");
            }
          }
        }
      }
      if (fl.flag_c == 1) {
        path(count_of_files, argv[files[i]], &fl);
        flag_c(&fl, count_for_c, count_of_lines);
      }
      count_of_lines = 0;
    }
    fclose(f);
  }
  return 0;
}

int flag_i(char *text, char *search_str) {
  int j = 0;
  int flag = 0;
  char temp_1;
  char temp_2;
  for (int i = 0; text[i] != '\0' && flag == 0; i++) {
    int temp_i = i;
    temp_1 = Lowercase_translation(text[i]);
    temp_2 = Lowercase_translation(search_str[j]);
    if (temp_1 == temp_2) {
      while (temp_1 == temp_2 && text[i] != '\0') {
        i++;
        j++;
        temp_1 = Lowercase_translation(text[i]);
        temp_2 = Lowercase_translation(search_str[j]);
      }
      if (search_str[j] == '\0') flag = 1;
      j = 0;
      i = temp_i;
    }
  }
  return flag;
}

char Lowercase_translation(char Sym) {
  if (Sym >= 65 && Sym <= 90)
    Sym = Sym + 32;
  else
    Sym = Sym;
  return Sym;
}

void get_opt(int argc, char **argv, flags *f) {
  int rez = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && strcmp(argv[i - 1], "-e") != 0) {
      rez = argv[i][1];
      switch (rez) {
        case 'e':
          f->flag_e = 1;
          break;
        case 'v':
          f->flag_v = 1;
          break;
        case 'i':
          f->flag_i = 1;
          break;
        case 'c':
          f->flag_c = 1;
          break;
        case 'l':
          f->flag_l = 1;
          break;
        case 's':
          f->flag_s = 1;
          break;
        case 'n':
          f->flag_n = 1;
          break;
        case 'h':
          f->flag_h = 1;
          break;
        case 'o':
          f->flag_o = 1;
          break;
        case '?':
          break;
        default:
          break;
      }
    }
  }
}

int search_files(int argc, char **argv, int files[], flags *fl) {
  int i = 1;
  int count = 0;
  int count_templates = 0;
  if (fl->flag_e == 1) {
    for (; strcmp(argv[i], "-e") != 0; i++) {
      if (argv[i][0] != '-') {
        files[count] = i;
        count++;
      }
    }
  }

  while (i < argc) {
    if (strcmp(argv[i], "-e") == 0) {
      if (i + 2 < argc) {
        i += 2;
        if (argv[i][0] != '-') {
          files[count] = i;
          count_templates = 1;
          count++;
          i++;
        } else if (count_templates == 0)
          count_templates++;
      } else {
        break;
      }
    } else if (argv[i][0] == '-')
      i++;
    else {
      if (count_templates != 0) {
        files[count] = i;
        count++;
        i++;
      } else {
        count_templates = 1;
        i++;
      }
    }
  }
  return count;
}

int search_templates(int argc, char **argv, int templates[], flags *fl) {
  int count_of_templates = 0;
  int i = 1;

  if (fl->flag_e == 1) {
    while (strcmp(argv[i], "-e") != 0) i++;
    i++;
    templates[count_of_templates] = i;
    i++;
    count_of_templates++;
  }

  if (count_of_templates == 0) {
    while (i < argc && argv[i][0] == '-') {
      i++;
    }
    templates[count_of_templates] = i;
    i++;
    count_of_templates++;
  }

  while (i < argc) {
    if (strcmp(argv[i], "-e") == 0) {
      i++;
      templates[count_of_templates] = i;
      count_of_templates++;
    }
    i++;
  }
  return count_of_templates;
}

void path(int count_of_files, char string[], flags *fl) {
  if (count_of_files > 1 && fl->flag_h == 0) printf("%s:", string);
}

int flag_l(char *string, char *search_string, flags *fl, char files[]) {
  // fl->flag_c = 0;
  fl->flag_n = 0;
  fl->flag_o = 0;
  int flag = check_flag_i_flag_v(fl, string, search_string);
  if (flag == 1 && fl->stop == 0) {
    printf(files);
    printf("\n");
    fl->stop = 1;
  }
  return flag;
}

void flag_c_calc(char *string, char *search_string, flags *fl, int *count) {
  int flag = 0;
  fl->flag_n = 0;
  fl->flag_o = 0;
  if (fl->flag_i == 1) {
    flag = flag_i(string, search_string);
  } else {
    flag = grep(string, search_string);
  }
  if (flag == 1) (*count)++;
}

int flag_n(char *string, char *search_string, flags *fl, int line_number,
           int count_of_files, char *file) {
  int flag = check_flag_i_flag_v(fl, string, search_string);
  if (flag == 1) {
    path(count_of_files, file, fl);
    if (fl->flag_o == 0)
      printf("%d:%s", line_number, string);
    else {
      printf("%d:%s", line_number, search_string);
      if (string[strlen(string) - 1] == '\n') printf("\n");
    }
  }
  return flag;
}

void flag_c(flags *fl, int count_for_c, int count_of_lines) {
  if (fl->flag_v == 0)
    printf("%d\n", count_for_c);
  else
    printf("%d\n", count_of_lines - count_for_c);
}

int flag_i_flag_v(char *string, char *search_string, flags *fl,
                  int count_of_files, char *file) {
  int flag = 0;
  if (fl->flag_c == 0 && fl->flag_l == 0 && fl->flag_n == 0) {
    if (fl->flag_o != 1 || fl->flag_v != 1) {
      flag = check_flag_i_flag_v(fl, string, search_string);
      if (flag == 1) {
        path(count_of_files, file, fl);
        if (fl->flag_o == 0)
          printf(string);
        else {
          printf(search_string);
          if (string[strlen(string) - 1] == '\n') printf("\n");
        }
      }
    }
  }
  return flag;
}

int check_flag_i_flag_v(flags *fl, char *string, char *search_string) {
  int flag = 0;
  if (fl->flag_i == 1)
    flag = flag_i(string, search_string);
  else
    flag = grep(string, search_string);
  if (fl->flag_v == 1) flag = !flag;
  return flag;
}

int flag_o(flags *fl, char *string, char *search_string, int count_of_files,
           char *file) {
  int flag = 0;
  if (grep(string, search_string) == 1) {
    flag = 1;
    path(count_of_files, file, fl);
    printf(search_string);
    if (string[strlen(string) - 1] == '\n') printf("\n");
  }
  return flag;
}

int sum_flags(flags *fl) {
  return (fl->flag_i + fl->flag_v + fl->flag_c + fl->flag_l + fl->flag_n +
          fl->flag_o);
}

int match(char *string, char *pattern, regex_t *re) {
  int status;
  if ((status = regcomp(re, pattern, REG_EXTENDED)) == 0)
    status = regexec(re, string, 0, NULL, 0);
  return (status);
}

int grep(char *text, char *search_str) {
  regex_t re;
  int retval = match(text, search_str, &re);
  retval = !retval;
  regfree(&re);
  return retval;
}
