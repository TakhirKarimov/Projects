#include <stdio.h>
typedef struct Node {
  char mini_str[500];
  int len;
  int _is_this_empty;
  int _line_break;
  struct Node *next;
  int f;
} Node;

int filling_array(FILE *f, char str[], int size, Node *node);
int size_of_file(FILE *f);
int init_list(Node **node);
int to_list(char *str, int start, int finish, Node *node, int f);
int check_empty_str(char str[], int);
int flag_b(Node *node);
void print_list(Node *node);
void add_count_and_tabulation(Node **, int count);
int calculate_digids(int num);
int flag_e(Node *node);
int flag_n(Node *node);
void flag_s(Node *node);
void flag_t(Node *node);
void flag_v(Node *node);
Node *remove_all_list(Node *node);
void delete_next_element(Node *p);

typedef struct flags {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int E;
  int T;
} flags;

void Flags(char *str[], flags *f, int);
int edit_list(Node *node, flags *f);