#include "s21_cat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  while (getopt(argc, argv, "benstvET") != -1) {
  }
  for (int i = optind; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (f == NULL || argc == 1) {
      printf("%s", "n/a");
    } else {
      flags fl = {0, 0, 0, 0, 0, 0, 0, 0};
      int size = size_of_file(f);
      char *str = (char *)calloc(size, sizeof(char));
      if (str != NULL) {
        Node *list = NULL;
        if (init_list(&list) != 1 && filling_array(f, str, size, list) != 1) {
          Flags(argv, &fl, argc);
          if (edit_list(list, &fl) == 0) print_list(list);
        }
        list = remove_all_list(list);
        free(str);
      }
    }
    fclose(f);
  }
  return 0;
}

int size_of_file(FILE *f) {
  fseek(f, 0, SEEK_END);
  int size = ftell(f);
  fseek(f, 0, SEEK_SET);
  return size;
}

int filling_array(FILE *f, char str[], int size, Node *node) {
  int start = 0;
  int finish = 0;
  int flag_to_exit = 0;
  while (finish < size && flag_to_exit == 0) {
    while (fscanf(f, "%c", &str[finish]) && str[finish] != '\n' &&
           finish < size && flag_to_exit == 0) {
      finish++;
    }
    if (to_list(str, start, finish, node, 0) == 1) {
      flag_to_exit = 1;
      break;
    }
    start = finish;
    size--;
  }
  if (str[size] == '\n') {
    if (to_list("\n", 0, 0, node, 1) == 1) {
      flag_to_exit = 1;
    }
  }
  return flag_to_exit;
}

int to_list(char *str, int start, int finish, Node *node, int f) {
  int flag_to_exit = 0;
  Node *tmp = (Node *)calloc(1, sizeof(Node));
  if (tmp == NULL) {
    flag_to_exit = 1;
  } else {
    tmp->len = finish - start;
    for (int i = 0; i < (tmp->len); i++, start++) {
      tmp->mini_str[i] = str[start];
    }
    tmp->mini_str[tmp->len] = '\0';
    tmp->f = f;
    tmp->_is_this_empty = check_empty_str(tmp->mini_str, tmp->len);
    tmp->_line_break = 1;
    tmp->next = NULL;
    Node *p = node;
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = tmp;
  }
  return flag_to_exit;
}

int init_list(Node **node) {
  *node = (Node *)calloc(1, sizeof(Node));
  int flag_to_exit = 0;
  if (*node != NULL) {
    (*node)->next = NULL;
    (*node)->len = 0;
    (*node)->_line_break = 0;
    (*node)->f = 0;
    (*node)->mini_str[0] = '\0';
  } else
    flag_to_exit = 1;
  return flag_to_exit;
}

int check_empty_str(char str[], int len) {
  int flag = 0;
  if ((str[0] == '\n' && str[1] == '\0') || str[0] == '\0') {
    if (len == 0) {
      flag = 1;
    }
  }
  return flag;
}

void add_count_and_tabulation(Node **tmp, int count) {
  int add_len = calculate_digids(count);
  (*tmp)->len = 7;

  int i = 0;
  while (i < (6 - add_len)) {
    (*tmp)->mini_str[i] = ' ';
    i++;
  }
  i = 5;
  while (count > 0) {
    (*tmp)->mini_str[i] = 48 + count % 10;
    count /= 10;
    i--;
  }
  (*tmp)->mini_str[6] = '\t';
  (*tmp)->_line_break = 0;
}

int calculate_digids(int num) {
  int count = 0;
  while (num != 0) {
    num /= 10;
    count++;
  }
  return count;
}

int flag_b(Node *node) {
  int flag_to_exit = 0;
  Node *p = node;
  Node *p_next = p->next;
  int count = 1;
  while (p->next != NULL && flag_to_exit == 0) {
    if (p->next->_is_this_empty == 0) {
      Node *tmp = (Node *)calloc(1, sizeof(Node));
      if (tmp == NULL) {
        flag_to_exit = 1;
        break;
      } else {
        add_count_and_tabulation(&tmp, count);
        tmp->next = p->next;
        p->next = tmp;
        count++;
        p = p->next->next;
        p_next = p_next->next;
      }
    } else {
      p = p->next;
      p_next = p_next->next;
    }
  }
  return flag_to_exit;
}

int flag_e(Node *node) {
  int flag_to_exit = 0;
  Node *p = node->next;
  while (p->next != NULL) {
    p->_is_this_empty = 0;
    if (p->_line_break == 1) {
      Node *tmp = (Node *)calloc(1, sizeof(Node));
      if (tmp == NULL) {
        flag_to_exit = 1;
        break;
      } else {
        p->_line_break = 0;
        tmp->_line_break = 1;
        tmp->len = 1;
        tmp->_is_this_empty = 1;
        tmp->mini_str[0] = '$';
        tmp->next = p->next;
        p->next = tmp;
        p = p->next->next;
      }
    } else {
      p = p->next;
    }
  }
  return flag_to_exit;
}

int flag_n(Node *node) {
  Node *p = node;
  Node *p_next = p->next;
  int count = 1;
  int flag_to_exit = 0;
  while (p->next != NULL) {
    if (p->next->f != 1) {
      Node *tmp = (Node *)calloc(1, sizeof(Node));
      if (tmp == NULL) {
        flag_to_exit = 1;
        break;
      } else {
        add_count_and_tabulation(&tmp, count);
        tmp->next = p->next;
        p->next = tmp;
        count++;
        p = p->next->next;
        p_next = p_next->next;
      }
    } else {
      break;
    }
  }
  return flag_to_exit;
}

void flag_s(Node *node) {
  Node *p = node->next;
  while (p != NULL) {
    if (p->_is_this_empty == 1) {
      while (p->next != NULL && p->next->_is_this_empty == 1) {
        delete_next_element(p);
      }
    }
    p = p->next;
  }
}

void flag_t(Node *node) {
  Node *p = node->next;
  while (p != NULL) {
    for (int i = 0; i < p->len; i++) {
      if (p->mini_str[i] == '\t') {
        p->len += 1;
        char temp = p->mini_str[i + 1];
        p->mini_str[i] = '^';
        p->mini_str[i + 1] = 'I';
        for (int j = p->len - 1; j > i + 1; j--) {
          p->mini_str[j] = p->mini_str[j - 1];
        }
        p->mini_str[i + 2] = temp;
      }
    }
    p = p->next;
  }
}

void delete_next_element(Node *p) {
  Node *tmp = p->next;
  p->next = p->next->next;
  free(tmp);
}

void print_list(Node *node) {
  Node *p = node->next;
  while (p != NULL) {
    for (int i = 0; i < (p->len); i++) {
      printf("%c", p->mini_str[i]);
    }
    if (p->next != NULL && p->_line_break == 1) {
      printf("%c", '\n');
    }
    p = p->next;
  }
}

void Flags(char *str[], flags *f, int n) {
  for (int q = 1; q < n - 1; q++) {
    for (int i = 0; str[q][i + 1] != '\0'; i++) {
      if (str[q][i] == '-') {
        while (str[q][i + 1] != '\0') {
          if (strlen(str[q]) > 2 && str[q][i + 1] == '-') {
            i++;
          }
          if (str[q][i + 1] == 'b') {
            (f)->b = 1;
          }
          if (str[q][i + 1] == 'e') {
            (f)->e = 1;
          }
          if (str[q][i + 1] == 'n') {
            (f)->n = 1;
          }
          if (str[q][i + 1] == 's') {
            (f)->s = 1;
          }
          if (str[q][i + 1] == 't') {
            (f)->t = 1;
          }
          if (str[q][i + 1] == 'v') {
            (f)->v = 1;
          }
          if (str[q][i + 1] == 'E') {
            (f)->E = 1;
          }
          if (str[q][i + 1] == 'T') {
            (f)->T = 1;
          }
          i++;
        }
      }
    }
  }
}

int edit_list(Node *node, flags *f) {
  int flag_to_exit = 0;
  if (f->s == 1 && flag_to_exit == 0) {
    flag_s(node);
  }
  if (f->b == 1 && flag_to_exit == 0) {
    if (flag_b(node) == 1) flag_to_exit = 1;
    if (f->n == 1) {
      f->n = 0;
    }
  }
  if (f->E == 1 && flag_to_exit == 0) {
    if (flag_e(node) == 1) flag_to_exit = 1;
  }
  if (f->e == 1 && flag_to_exit == 0) {
    if (f->v == 1) {
      f->v = 0;
    }
    if (f->t == 1) {
      f->t = 0;
      f->T = 1;
    }
    flag_v(node);
    if (flag_e(node) == 1) flag_to_exit = 1;
  }
  if (f->T == 1 && flag_to_exit == 0) {
    flag_t(node);
  }
  if (f->t == 1 && flag_to_exit == 0) {
    if (f->v == 1) {
      f->v = 0;
    }
    flag_v(node);
    flag_t(node);
  }
  if (f->v == 1 && flag_to_exit == 0) flag_v(node);
  if (f->n == 1 && flag_to_exit == 0) {
    if (f->e == 1) {
      if (flag_b(node) == 1) flag_to_exit = 1;
    } else {
      if (flag_n(node) == 1) flag_to_exit = 1;
    }
  }
  return flag_to_exit;
}

void flag_v(Node *node) {
  Node *p = node;
  while (p != NULL) {
    for (int i = 0; i < p->len; i++) {
      if (p->mini_str[i] < 32 && p->mini_str[i] != '\t') {
        int temp = p->mini_str[i] + 64;
        p->len += 1;
        p->mini_str[i] = '^';
        for (int j = p->len - 1; j > i + 1; j--) {
          p->mini_str[j] = p->mini_str[j - 1];
        }
        p->mini_str[i + 1] = temp;
      }
    }
    p = p->next;
  }
}

Node *remove_all_list(Node *node) {
  while (node != NULL) {
    Node *p = node;
    node = node->next;
    free(p);
  }
  return node;
}
