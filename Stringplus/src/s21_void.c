#include "s21_void.h"

// int main() {
//   char* buff = "     asdfADASSA5522 ASasdaspqp112212    ";
//   char* buff2 = " 2";
//   //char* reference = "asdfADASSA5522 ASasdaspqp11221";
//   char* buff3 = s21_trim(buff, buff2);
// }

s21_size_t s21_len(const char *s) {
  s21_size_t count = 0;

  if (s != s21_NULL) {
    while (s[count] != '\0') {
      count++;
    }
  }
  return count;
}

void *s21_to_upper(const char *str) {
  char *new_str = s21_NULL;

  if (str != s21_NULL && str[0] != '\0') {
    s21_size_t src_s = s21_len(str);  // длина  src
    if (src_s != 0) {
      new_str = malloc((src_s + 1) * sizeof(char));
      new_str[src_s] = '\0';
    }
    // printf("%ld\n", len(str));
    for (s21_size_t i = 0; i < src_s && new_str != s21_NULL; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
        new_str[i] = str[i] - ('a' - 'A');
      } else {
        new_str[i] = str[i];
      }
    }
  } else if (str == s21_NULL) {
    ;
  } else {
    new_str = malloc(1 * sizeof(char));
    new_str[0] = '\0';
  }
  return new_str;
}

void *s21_to_lower(const char *str) {
  char *new_str = s21_NULL;

  if (str != s21_NULL && str[0] != '\0') {
    s21_size_t src_s = s21_len(str);  // длина  src
    if (src_s != 0) {
      new_str = malloc((src_s + 1) * sizeof(char));
      new_str[src_s] = '\0';
    }
    for (s21_size_t i = 0; i < src_s && new_str != s21_NULL; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
        new_str[i] = str[i] + ('a' - 'A');
      } else {
        new_str[i] = str[i];
      }
    }
  } else if (str == s21_NULL) {
    ;
  } else {
    new_str = malloc(1 * sizeof(char));
    new_str[0] = '\0';
  }
  return new_str;
}

// void *s21_insert(const char *src, const char *str, size_t start_index) {
//   char *new_str = NULL;

//   if (src != NULL && src[0] != '\0') {
//     size_t count = 0;
//     size_t str_s = s21_len(str);
//     size_t src_s = s21_len(src);

//     if (start_index < src_s) {
//       new_str =
//           malloc(str_s * sizeof(char) + src_s * sizeof(char) + sizeof(char));
//       new_str[str_s + src_s] = '\0';

//       if (new_str != NULL) {
//         while (count < start_index) {
//           new_str[count] = src[count];
//           count++;
//         }

//         for (size_t i = 0; i < str_s; i++) {
//           new_str[count + i] = str[i];
//         }

//         while (count < (src_s + str_s)) {
//           new_str[count + str_s] = src[count];
//           count++;
//         }
//       }
//     }
//   } else if (src == NULL) {
//     ;
//   } else {
//     new_str = malloc(sizeof(char));
//     new_str[0] = '\0';
//   }

//   return new_str;
// }
void s21_trim_before_after(const char *src, const char *trim_chars,
                           s21_size_t *count, s21_size_t *recount) {
  s21_size_t src_s = 0;
  s21_size_t trim_s = 0;
  int flag = 0;

  if (s21_len(src) != 0 && s21_len(trim_chars) != 0) {
    src_s = s21_len(src);          // длина  src
    trim_s = s21_len(trim_chars);  // длина trim_chars
    flag = 1;
  }

  for (s21_size_t i = 0; i < src_s && flag == 1;
       i++) {  // считаем кол-во удаляемых символов до печатуемого текста
    s21_size_t r = 0;
    for (s21_size_t j = 0; j < trim_s; j++) {
      if (src[i] == trim_chars[j]) {
        *count = *count + 1;
      } else {
        r++;
      }
    }
    if (r == trim_s) {
      flag = 2;
    }
  }

  for (s21_size_t i = src_s - 1; (i > 0) && (flag > 0) && (*count < src_s);
       i--) {  // считаем кол-во удаляемых символов печатуемого текста
    s21_size_t r = 0;
    for (s21_size_t j = 0; j < trim_s; j++) {
      if (src[i] == trim_chars[j]) {
        *recount = *recount + 1;
      } else {
        r++;
      }
    }
    if (r == trim_s) {
      flag = 0;
    }
  }
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *new_str = s21_NULL;

  if ((src != s21_NULL) && (*src != '\0')) {
    s21_size_t src_s = s21_len(src);  // длина  src
    if (src_s != 0) {
      s21_size_t count = 0;
      s21_size_t recount = 0;

      s21_trim_before_after(src, trim_chars, &count, &recount);
      s21_size_t new_size = src_s - count - recount;

      new_str = malloc((new_size + 1) * sizeof(char));

      for (s21_size_t i = 0; (i < new_size) && (count != src_s); i++) {
        new_str[i] = src[count + i];
      }
      new_str[new_size] = '\0';
    }
  } else if (src == s21_NULL) {
    ;
  } else {
    new_str = malloc(sizeof(char));
    new_str[0] = '\0';
  }
  return new_str;
}
